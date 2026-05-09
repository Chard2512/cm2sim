#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "io/parser.hpp"
#include "io/strutils.hpp"
#define PROJECT_NAME "sfcm2"
#define VERSION "0.1"

void usage(const std::string &progName)
{
    std::cout << "Usage: " << progName << " [OPTION]... [FILE]\n";
    std::cout << "Run a simulation of a Circuit Maker 2 module.\n\n";
    std::cout << "Example: " << progName << " savestring.txt \n\n";
    std::cout << "Arguments:\n";
    std::cout << std::left
              << std::setw(30) << "  -p, --fps=RATE"
              << "Set simulation framerate (default: 60).\n"
              << std::setw(30) << "  -h, --help"
              << "Prints this help message.\n"
              << std::setw(30) << "  -t, --tickrate=RATE"
              << "Set simulation tickrate (default: 20).\n"
              << std::setw(30) << "  --version"
              << "Prints program's version." << std::endl;
}

bool loadModule(Module &module, std::string filepath)
{
    std::ifstream file(filepath);
    if (!file.is_open())
    {
        std::cerr << "Could not open file \"" << filepath << "\"." << std::endl;
        return false;
    }

    std::string savestring;
    std::getline(file, savestring);

    auto fields = split(savestring, '?');
    auto blockstrings = split(fields[0], ';');
    auto wirestrings = split(fields[1], ';');

    for (auto blockstring : blockstrings)
    {
        if (!blockstring.empty())
        {
            auto newBlock = parseBlockstring(blockstring);
            if (newBlock == nullptr)
            {
                return false;
            }
            module.addBlock(newBlock);
        }
    }

    for (auto wirestring : wirestrings)
    {
        if (!wirestring.empty())
        {
            auto blocksStr = split(wirestring, ',');
            if (blocksStr.size() != 2)
            {
                std::cerr << "ERROR: trying to parse a malformed wirestring." << std::endl;
                return false;
            }
            
            uint64_t block0Index, block1Index;

            try {
                block0Index = std::stoull(blocksStr[0]);
                block1Index = std::stoull(blocksStr[1]);
            } catch (const std::invalid_argument&) {
                std::cerr << "ERROR: Invalid block index in wirestring (non-numeric value)." << std::endl;
                return false;
            }

            if (block0Index == 0 || block1Index == 0) {
                std::cerr << "ERROR: Block index cannot be 0 (indices are 1-based)." << std::endl;
                return false;
            }

            block0Index--;
            block1Index--;

            uint64_t blockCount = module.getBlockCount();
            if (block0Index >= blockCount || block1Index >= blockCount) {
                std::cerr << "ERROR: Block index out of range." << std::endl;
                return false;
            }

            Block *block0 = module.getBlock(block0Index);
            Block *block1 = module.getBlock(block1Index);

            if (!block0 || !block1) {
                std::cerr << "ERROR: Null block reference encountered." << std::endl;
                return false;
            }

            bool connectionExists = false;
            for (const auto* output : block0->getOutputs()) {
                if (output == block1) {
                    connectionExists = true;
                    break;
                }
            }

            if (connectionExists) {
                std::cerr << "WARNING: Duplicate connection between blocks " 
                        << block0Index + 1 << " and " << block1Index + 1 
                        << " - skipping." << std::endl;
                continue;
            }

            module.connectBlocks(block0, block1);
        }
    }

    return true;
}

Block *parseBlockstring(std::string blockstring)
{
    if (blockstring.empty())
    {
        std::cerr << "ERROR: Empty blockstring." << std::endl;
        return nullptr;
    }

    std::vector<std::string> blockParams = split(blockstring, ',');
    if (blockParams.size() != 6)
    {
        std::cerr << "ERROR: Malformed blockstring - expected 6 parameters, got " 
                  << blockParams.size() << ": \"" << blockstring << "\"" << std::endl;
        return nullptr;
    }

    int rawBlockID;
    try {
        rawBlockID = std::stoi(blockParams[0]);
    } catch (const std::invalid_argument&) {
        std::cerr << "ERROR: Invalid BlockID (non-numeric): \"" 
                  << blockParams[0] << "\"" << std::endl;
        return nullptr;
    } catch (const std::out_of_range&) {
        std::cerr << "ERROR: BlockID value out of range: \"" 
                  << blockParams[0] << "\"" << std::endl;
        return nullptr;
    }
    BlockID blockID = static_cast<BlockID>(rawBlockID);

    int rawState;
    try {
        rawState = std::stoi(blockParams[1]);
    } catch (const std::invalid_argument&) {
        std::cerr << "ERROR: Invalid state value (non-numeric): \"" 
                  << blockParams[1] << "\"" << std::endl;
        return nullptr;
    } catch (const std::out_of_range&) {
        std::cerr << "ERROR: State value out of range: \"" 
                  << blockParams[1] << "\"" << std::endl;
        return nullptr;
    }

    if (rawState != 0 && rawState != 1) {
        std::cerr << "ERROR: Invalid state value: " << rawState 
                  << " (must be 0 or 1)" << std::endl;
        return nullptr;
    }
    bool state = static_cast<bool>(rawState);

    float posX, posY;
    try {
        posX = std::stof(blockParams[2]);
        posY = std::stof(blockParams[4]);
    } catch (const std::invalid_argument&) {
        std::cerr << "ERROR: Invalid position coordinates (non-numeric): \"" 
                  << blockParams[2] << "\", \"" << blockParams[4] << "\"" << std::endl;
        return nullptr;
    } catch (const std::out_of_range&) {
        std::cerr << "ERROR: Position coordinates out of range: \"" 
                  << blockParams[2] << "\", \"" << blockParams[4] << "\"" << std::endl;
        return nullptr;
    }

    sf::Vector2f pos(posX, posY);

    std::vector<float> properties;
    if (!blockParams[5].empty())
    {
        auto propertyStrings = split(blockParams[5], '+');

        for (size_t i = 0; i < propertyStrings.size(); i++)
        {
            try {

                float property = std::stof(propertyStrings[i]);
                properties.push_back(property);

            } catch (const std::invalid_argument&) {
                std::cerr << "ERROR: Invalid property value (non-numeric): \"" 
                          << propertyStrings[i] << "\"" << std::endl;
                return nullptr;
            } catch (const std::out_of_range&) {
                std::cerr << "ERROR: Property value out of range: \"" 
                          << propertyStrings[i] << "\"" << std::endl;
                return nullptr;
            }
        }
    }
    
    Block* newBlock = BlockFactory::createBlock(blockID, state, pos, properties);

    if (!newBlock) {
        std::cerr << "ERROR: Failed to create block of type " 
                  << static_cast<int>(blockID) << std::endl;
        return nullptr;
    }

     return newBlock;
}

ArgParseStatus parseArgs(Args &args, int argc, char *argv[])
{
    std::string progName = argv[0];

    if (argc == 1) {
        usage(progName);
        return ArgParseStatus::ExitSuccess;
    }

    for (int i = 1; i < argc; i++)
    {
        const std::string arg = argv[i];

        if (arg[0] == '-')
        {
            if (arg[1] == '-')
            {
                std::string op = arg.substr(2);
                if (op == "help")
                {
                    usage(progName);
                    return ArgParseStatus::ExitSuccess;
                }
                else if (op == "version")
                {
                    std::cout << PROJECT_NAME << " " << VERSION << std::endl;
                    return ArgParseStatus::ExitSuccess;
                }
                else if (startsWith(op, "tickrate="))
                {
                    args.simConfig.tickrate = std::stod(substrFromCharStart(op, '='));
                }
                else if (startsWith(op, "fps="))
                {
                    args.simConfig.framerate = std::stod(substrFromCharStart(op, '='));
                }
                else
                {
                    std::cerr << "Invalid option '" << op << "'." << std::endl;
                    return ArgParseStatus::ExitFailure;
                }
            }
            else
            {
                std::string ops = arg.substr(1);
                for (size_t j = 0; j < ops.size(); j++)
                {
                    if (j == 0)
                    {
                        if (ops[j] == 'h')
                        {
                            usage(progName);
                            return ArgParseStatus::ExitSuccess;
                        }
                        else if (ops[j] == 'p')
                        {
                            if (i + 1 >= argc)
                            {
                                std::cerr << "Run at which FPS??" << std::endl;
                                return ArgParseStatus::ExitFailure;
                            }
                            args.simConfig.framerate = std::stod(argv[i + 1]);
                            i++;
                            break;
                        }
                        if (ops[j] == 't')
                        {
                            if (i + 1 >= argc)
                            {
                                std::cerr << "I require a tickrate definition! :<" << std::endl;
                                return ArgParseStatus::ExitFailure;
                            }
                            args.simConfig.tickrate = std::stod(argv[i + 1]);
                            i++;

                            if (args.simConfig.tickrate > 1000000)
                            {
                                std::cerr << "Ooh, that's too big tickrate, Senpai! O.O\n";
                                std::cerr << "I can't handle that much!\n";
                                return ArgParseStatus::ExitFailure;
                            }

                            break;
                        }
                    }
                    else
                    {
                        std::cerr << "Invalid option '" << ops[j] << "'." << std::endl;
                        return ArgParseStatus::ExitFailure;
                    }
                }
            }
        }
        else
        {
            if (args.moduleFilePath.empty())
            {
                args.moduleFilePath = arg;
            }
        }
    }

    return ArgParseStatus::Continue;
}