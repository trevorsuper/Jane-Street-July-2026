#include <iostream>
#include <cstdint>
#include <array>
#include <iomanip>
#include <bitset>
#include <algorithm>

using s32 = std::int32_t;
using u64 = std::uint64_t;
using u32 = std::uint32_t;
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

void compute_math_steps(std::array<u32, 63> *math_steps, std::array<s32, 11> *known_steps)
{
	s32 score = 0;
	u32 math_walk = 0;
	bool altitude = 1;
	
	u32 math_walk_18 = 0;
	s32 score_18_checkpoint;
	bool altitude_18_checkpoint;
	
	u8 k = 0;
	std::cout << k << "\n";
	
	std::bitset<32> part1_bits(math_walk);
	std::bitset<32> part2_bits(math_walk_18);
	
	for (int n = 0; n <= 53; ++n) {
		std::bitset<32> part1_bits(math_walk);
		std::bitset<32> part2_bits(math_walk_18);
		if (n == 0) {
			(*math_steps)[0] = 0;
		}
		
		else if (n > 0 && n <= 18 && k == 0) {
			if (n % 3 != 0) {
				if (part1_bits[n] == 0) {
					score += n;
					(*math_steps)[n] = score;
				}
				else if (part1_bits[n] == 1 && altitude == 0) {
					score *= n;
					(*math_steps)[n] = score;
					altitude = 1;
				}
				else if (part1_bits[n] == 1 && altitude == 1) {
					score /= n;
					(*math_steps)[n] = score;
					altitude = 0;
				}
			}
			else if (n % 3 == 0) {
				if (part1_bits[n] == 0) {
					score += n;
					(*math_steps)[n] = score;
				}
				else if (part1_bits[n] == 1 && altitude == 0) {
					score *= n;
					(*math_steps)[n] = score;
					altitude = 1;
				}
				else if (part1_bits[n] == 1 && altitude == 1) {
					score /= n;
					(*math_steps)[n] = score;
					altitude = 0;
				}
				
				if (n == 18) {
					score_18_checkpoint = score;
					altitude_18_checkpoint = altitude;
					k = 7;
				}
				
				auto it = std::ranges::find(*known_steps, score);
				if (it == known_steps->end()) {
					std::cout << "value not found, resetting\n";
					n = -1;
					math_walk += 1;
					score = 0;
					altitude = 1;
				}
				
			}
			std::cout << "n: " << n 
					  << " altitude: " << altitude 
					  << " score: " << score 
					  << " math_walk: " << math_walk 
					  << " part1_bits[n]: " << part1_bits[n] <<"\n";
		}
		
		else if (n >= 18 && k >= 4) {
			if ((n - 18) % k != 0) {
				if (part2_bits[n - 18] == 0) {
					score += n;
					(*math_steps)[n] = score;
				}
				else if (part2_bits[n - 18] == 1 && altitude == 0) {
					score *= n;
					(*math_steps)[n] = score;
					altitude = 1;
				}
				else if (part2_bits[n - 18] == 1 && altitude == 1) {
					score /= n;
					(*math_steps)[n] = score;
					altitude = 0;
				}
			}
			else if ((n - 18) % k == 0) {
				if (part2_bits[n - 18] == 0) {
					score += n;
					(*math_steps)[n] = score;
				}
				else if (part2_bits[n - 18] == 1 && altitude == 0) {
					score *= n;
					(*math_steps)[n] = score;
					altitude = 1;
				}
				else if (part2_bits[n - 18] == 1 && altitude == 1) {
					score /= n;
					(*math_steps)[n] = score;
					altitude = 0;
				}
				auto it = std::ranges::find(*known_steps, score);
				if (it == known_steps->end()) {
					//++k;
					//std::cout << "n: " << n << " ABOVE 19 not found, setting k = " << (int)k << "\n";
					n = 18;
					math_walk_18 += 1;
					score = score_18_checkpoint;
					altitude = altitude_18_checkpoint;
				}
			}
			std::cout << "n: " << n 
					  << " altitude: " << altitude 
					  << " score: " << score 
					  << " math_walk_18: " << math_walk_18 
					  << " part2_bits[n]: " << part2_bits[n - 18] <<"\n";
		}
		
		/*else if (k != 0 && n >= 22) {
			if (n % k == 0) {
				
			}
			else if (n % k != 0) {
				
			}
		}
		
		else if (k != 0 && n >= 40) {
			// time to exit loop check
		}*/
		
	}
	std::cout << "math_walk " << math_walk << "\n";
	std::cout << "math_walk_18 " << math_walk_18 << "\n";
	std::cout << "score_18_checkpoint " << score_18_checkpoint << "\n";
	std::cout << "altitude_18_checkpoint " << altitude_18_checkpoint << "\n";
	
	std::cout << "score: " << score << "\n";
	
	std::cout << "math_steps: ";
	for (int n = 0; n <= 53; ++n) {
		std::cout << "[" << n << "] " << (int)(*math_steps)[n] << "\n";
	}
	std::cout << "known_steps: ";
	for (int n = 0; n < 11; ++n) {
		std::cout << "[" << n << "] " << (int)(*known_steps)[n] << "\n";
	}
}

int main()
{
	std::array<u32, 63> math_steps = {0};
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
	// X -------->
	}};
	
	square::print_board(knight_board);
	
	return 0;
}
