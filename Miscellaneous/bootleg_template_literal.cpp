#include <iostream>
#include <cstdlib>
#include <vector> 
// #include <array>

namespace RE {
    void Generate_Fractal() { 
        // naming convention inspiration from a music piece
        std::cerr << "[PARSE_ERROR]: incorrect template literal syntax";
        std::exit(EXIT_FAILURE);
    }

    // [[__attribute_maybe_unused__]] int8_t LINEAR_INCREMENTOR {1};
    [[maybe_unused]] int32_t LINEAR_INCREMENTOR {sizeof(char)};
}

int32_t main(int32_t argc, char *argv[]) {
    std::string interpolatedVarInput {};
    std::string interpolatedVarContent {}; // long unsigned int

    std::cout << "Enter template literal: ";
    // std::cin >> interpolatedVarInput;
    std::getline(std::cin, interpolatedVarInput);

    // interpolatedVarInput.end() = "";

    if (interpolatedVarInput[0] != '$') {
        RE::Generate_Fractal();
    }

    if (interpolatedVarInput[1] != '[') {
        RE::Generate_Fractal();
    }

    std::cout << "Enter interpolation variable content: ";
    std::getline(std::cin, interpolatedVarContent);

    std::string lexicalBuffer; 

    // while (cx != ']') {
    // }

    const int32_t MAX_LITERAL_SIZE {static_cast<int32_t>(interpolatedVarInput.size())}; // const int32_t 
    std::cout << "\ninterpolated var size: " << (interpolatedVarInput.size() - 3) << std::endl;
    char cx;

    // $[hello]
    // $ == valid
    // [ == valid 
    // <content> - MAX_SIZE + 2 
    // ]

    // int32_t LEX_COUNTER {0};

    for (int inx {2}; /* will skip 2 */ inx < (MAX_LITERAL_SIZE); inx = {std::plus<>()(inx, RE::LINEAR_INCREMENTOR)}) {
        cx = interpolatedVarInput[inx];

        if (cx == ']') { break; } 
        // lexicalBuffer[LEX_COUNTER] = cx; /* this will not execute if ] s*/
        lexicalBuffer.push_back(cx);

        // (cx == ']') ? break /* doesnt work because break is a keyword and not an expression evaluator */
                    // : lexicalBuffer[LEX_COUNTER] = cx; 

        // LEX_COUNTER = std::plus<>()(LEX_COUNTER, RE::LINEAR_INCREMENTOR);
    }

    std::string finalBuffer = static_cast<std::string>(lexicalBuffer); // i hate myself 
    std::cout << "buffer recieved: " << finalBuffer << "\n" << std::endl;

    std::cout << interpolatedVarInput << ": ";
    // interpolatedVarInput = interpolatedVarContent;
    std::swap(interpolatedVarInput, interpolatedVarContent);

    std::cout << interpolatedVarInput << std::endl;
    std::cout << std::endl;

    return EXIT_SUCCESS;
}
