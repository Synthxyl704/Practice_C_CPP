#include <iostream> 
#include <cstdlib> 
#include <cstdint>
#include <variant>
#include <memory>
#include <random>
#include <vector>
#include <optional>
#include <iomanip>

#define ESO std::variant<int32_t, float, std::string>;

static_assert(sizeof(int32_t) == 4);

auto smartPtr() -> void {
    std::unique_ptr<int32_t> ptr = std::make_unique<int32_t>(67);
    std::cout << "addressof(ptr): " << &ptr << " // valueat(*ptr): " << *ptr;

    std::unique_ptr<std::string> str = std::make_unique<std::string>("\n\nIso");
    *str += "Aris\n";
    std::cout << *str; // Iso += Aris; "IsoAris"

    std::shared_ptr<int32_t[]> arr = std::make_shared<int32_t[]>(2, 67); // {67, 67}
    std::shared_ptr<int32_t[]> exr = std::make_shared_for_overwrite<int32_t[]>(3); // raw, not zero-inited
}

// auto optionalFunc(int32_t numeric) -> std::optional<int32_t> {
//     return {(numeric == 67) ? std::optional<int32_t>(numeric) : std::nullopt};
// }

auto optionalFunc(int32_t numeric) -> std::optional<int32_t> {
    if (numeric == 67) 
        return numeric;   // implicit: int32_t -> optional<int32_t>
    return std::nullopt;  // or just return {}; 
}

constexpr int32_t FXconst(int32_t num) { 
    static int32_t var {num}; // this wouldnt work in C++17, works from C++23 onwards
    return var;
}

// constexpr auto getSomeNumber() -> int32_t {
//     std::random_device device;
//     std::mt19937 generateRandomNum(device());
//     std::uniform_int_distribution<std::mt19937::result_type> range100(1, 100);

//     return range100(generateRandomNum);
// }

// auto FX(int32_t someFlag = true) -> void {
//     // if consteval { int32_t hi {67}; } else { return; }

//     const uint32_t SOME_PR_NUM_1 {getSomeNumber()}; // works
//     constexpr uint32_t SOME_PR_NUM_1 {getSomeNumber()}; // doesnt work
// }

auto functionZero(int32_t someFlag = true) -> void {
    auto constexpr getSomeNumber = [](void) -> int32_t {
        std::random_device device;
        std::mt19937 generateRandomNum(device());
        std::uniform_int_distribution<std::mt19937::result_type> range100(1, 100);
        return static_cast<int32_t>(range100(generateRandomNum));
    }; 
    
    const uint32_t SOME_PR_NUM_1 {getSomeNumber()}; // lambda evalutes and assigns at runtime
    // constexpr uint32_t SOME_PR_NUM_2 {getSomeNumber()}; // still doesnt work
}

template <uint32_t SeedNum> 
struct CompileTimeRNG {
    static constexpr uint32_t next(uint32_t& state) {
        uint32_t XORVAR = state;
        {
            XORVAR ^= XORVAR << 5; XORVAR ^= XORVAR >> 10; 
            XORVAR ^= XORVAR << 2;  
        }
        state = XORVAR; 
        return state;
    }
};

constexpr uint32_t generateNumber() {
    uint32_t state {69420};
    return {
         CompileTimeRNG<0>::next(state) % 100 + 1
    };
}

// static_assert(SOME_PR_NUM_1 == generateNumber(), "NOT DEFINED"); 
constexpr uint32_t SOME_PR_NUM_1 = generateNumber(); // works

// template <typename dataType>
// void onlyINT(dataType num) {
//     static_assert(std::is_integral_v<dataType>, "data type must be an integer");
// }

int32_t main(int32_t argc, char *argv[]) {
    std::cout << "variable shit:\n";
    auto v1 = [x = 67](void) { return x; };
    std::cout << v1();
    
    auto [v2, v3] = std::pair(69, 420);
    std::cout << " | " << v2 << " / " << v3;
    std::cout << std::cout.fill('1');  
    std::cout << std::setw(5) << "-d" << '\n'; // this might be the worst thing ever

    std::cout << "\n\n"; 
    
    smartPtr();
    
    // onlyINT<int32_t>(42);    
    // onlyINT<float>(3.14); 

    // std::cout << std::boolalpha << std::is_integral_v<std::string> << "\n";

    functionZero();

    return EXIT_SUCCESS;
}
