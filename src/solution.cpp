#include <iostream>
#include <cstdint>
#include <array>
#include <iomanip>
#include <bitset>

using s32 = std::int32_t;
using u64 = std::uint64_t;
using u8 = std::uint8_t;

void compute_math_steps();
void print_math_steps();

struct square {
	s32 score;
	const u8 x;
	const u8 y;
	const u8 section;
	bool has_tower;
	const bool predetermined_score;
	
	template<std::size_t n>
	static void print_board(const std::array<square, n> &board)
	{
		std::cout << "{Score Section Tower}\n";
		int i = 0;
		for (const auto& sq : board) {
			std::cout << "{" 
					  << std::left << std::setw(7) << sq.score 
					  << std::setw(4) << static_cast<int>(sq.section) 
					  << sq.has_tower << "} ";
			if (++i % 8 == 0) {
				std::cout << "\n";
			}
		}
	}
	
};

struct knight {
	s32 score;
	u8 x;
	u8 y;
	u8 section;
	bool altitude;
};

void compute_math_steps(std::array<u8, 63> *math_steps, std::array<s32, 11> *known_steps)
{
	u64 math_walk = 0b0000000000000000000000000000000000000000000000000000000000000000;
	(*known_steps)[0] = 0;
	u8 k = 0;
	bool altitude = 1;
	
	std::bitset<64> bits(math_walk);
	
	for (u8 n = 0; n < 64; ++n) {
		std::cout << bits[n] << "\n";
		if (n == 0) {
			(*math_steps)[0] = 0;
		}
		else if (n <= 18 && n % 3 == 0) {
			if (altitude == 1) {
				
			} else if (altitude == 0) {
				
			}
			
		} else if (n > 19 && k == 0) {
			if (altitude == 1) {
				
			} else if (altitude == 0) {
				
			}
			
		} else if (k != 0 && n >= 22 && n % k == 0) {
			if (altitude == 1) {
				
			} else if (altitude == 0) {
				
			}
		}
	}
}

int main()
{
	std::array<u8, 63> math_steps = {0};
	std::array<s32, 11> known_steps {528, 449, 750, 88, 272, 1, 16, 23, 138, 37, 1100};
	
	compute_math_steps(&math_steps, &known_steps);
	
	std::array<square, 64> knight_board = {{
/* ^ */	{-1, 1, 8, 1, 0, 0}, {-1, 2, 8, 1, 0, 0}, {-1, 3, 8, 1, 0, 0}, {-1, 4, 8, 1, 0, 0}, {-1, 5, 8, 1, 0, 0}, {37, 6, 8, 2, 0, 1}, {-1, 7, 8, 2, 0, 0}, {1100, 8, 8, 2, 0, 1},
/* | */	{-1, 1, 7, 3, 0, 0}, {-1, 2, 7, 3, 0, 0}, {-1, 3, 7, 3, 0, 0}, {-1, 4, 7, 4, 0, 0}, {-1, 5, 7, 4, 0, 0}, {-1, 6, 7, 5, 0, 0}, {-1, 7, 7, 5, 0, 0}, {-1, 8, 7, 2, 0, 0},
/* | */	{-1, 1, 6, 3, 0, 0}, {-1, 2, 6, 7, 0, 0}, {-1, 3, 6, 3, 0, 0}, {23, 4, 6, 4, 0, 1}, {-1, 5, 6, 4, 0, 0}, {138, 6, 6, 4, 0, 1}, {-1, 7, 6, 5, 0, 0}, {-1, 8, 6, 2, 0, 0},
/* | */	{528, 1, 5, 6, 0, 1}, {-1, 2, 5, 7, 0, 0}, {-1, 3, 5, 7, 0, 0}, {-1, 4, 5, 8, 0, 0}, {-1, 5, 5, 8, 0, 0}, {-1, 6, 5, 9, 0, 0}, {-1, 7, 5, 5, 0, 0}, {-1, 8, 5, 5, 0, 0},
/* | */	{-1, 1, 4, 6, 0, 0}, {449, 2, 4, 6, 0, 1}, {-1, 3, 4, 7, 0, 0}, {-1, 4, 4, 8, 0, 0}, {16, 5, 4, 8, 0, 1}, {-1, 6, 4, 9, 0, 0}, {-1, 7, 4, 9, 0, 0}, {-1, 8, 4, 13, 0, 0},
/* | */	{-1, 1, 3, 6, 0, 0}, {750, 2, 3, 10, 0, 1}, {-1, 3, 3, 7, 0, 0}, {88, 4, 3, 11, 0, 1}, {-1, 5, 3, 9, 0, 0}, {272, 6, 3, 9, 0, 1}, {1, 7, 3, 12, 0, 1}, {-1, 8, 3, 13, 0, 0},
/* | */	{-1, 1, 2, 6, 0, 0},  {-1, 2, 2, 10, 0, 0}, {-1, 3, 2, 11, 0, 0}, {-1, 4, 2, 11, 0, 0}, {-1, 5, 2, 11, 0, 0}, {-1, 6, 2, 12, 0, 0},  {-1, 7, 2, 12, 0, 0}, {-1, 8, 2, 13, 0, 0},
/* | */	{0, 1, 1, 10, 0, 1},   {-1, 2, 1, 10, 0, 0}, {-1, 3, 1, 10, 0, 0}, {-1, 4, 1, 11, 0, 0}, {-1, 5, 1, 12, 0, 0}, {-1, 6, 1, 12, 0, 0},  {-1, 7, 1, 13, 0, 0}, {-1, 8, 1, 13, 0, 0},
/* Y */	
	// X --------------->
	}};
	
	square::print_board(knight_board);
	
	return 0;
}
