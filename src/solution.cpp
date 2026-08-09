#include <iostream>
#include <cstdint>
#include <array>
#include <iomanip>
#include <bitset>
#include <algorithm>

using s64 = std::int64_t;
using s32 = std::int32_t;
using u64 = std::uint64_t;
using u32 = std::uint32_t;
using u8 = std::uint8_t;

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
		for (const auto &sq : board) {
			std::cout << "{" 
					  << std::left << std::setw(7) << sq.score 
					  << std::setw(4) << static_cast<int>(sq.section) 
					  << sq.has_tower << "} ";
			if (++i % 8 == 0) {
				std::cout << "\n";
			}
		}
	}
	
	template<std::size_t n>
	static void print_square(std::array<square, n> &board, u8 target_x, u8 target_y) {
		for (const auto &sq : board) {
			if (sq.x == target_x && sq.y == target_y) {
				std::cout << "Square (" << static_cast<int>(target_x) << ", " << static_cast<int>(target_y) << "):"
                      << " Score: " << sq.score
                      << " Section: " << static_cast<int>(sq.section)
                      << " Square Has Tower: " << (sq.has_tower ? "Yes" : "No")
                      << " Predetermined Score: " << (sq.predetermined_score ? "Yes" : "No") << "\n";
			}
		}
	}
	
	static square &get_square_at(std::array<square, 64> &board, u8 x, u8 y) {
		u8 index = (8 - y) * 8 + (x - 1);
		return board.at(index);
	}
	
	template<std::size_t n>
	static bool does_section_have_tower(std::array<square, n> &board, u8 section_target) {
		for (const auto &sq : board) {
			if (sq.section == section_target) {
				if (sq.has_tower == 1) {
					return 1;
				}
			}
		}
		return 0;
	}
	
	template<std::size_t n>
	static bool does_section_have_tower(std::array<square, n> &board, u8 x, u8 y) {
		square target_square = board.at((8 - y) * 8 + (x - 1));
		for (const auto &sq : board) {
			if (sq.section == target_square.section) {
				if (sq.has_tower == 1) {
					return 1;
				}
			}
		}
		return 0;
	}
	
	template<std::size_t n>
	static bool do_all_sections_have_towers(std::array<square, n> &board) {
		for (u8 i = 1; i <= 13; ++i) {
			if (!does_section_have_tower(board, i)) {
				return 0;
			}
		}
		return 1;
	}
	
	static int add_neighbor_sums(std::array<square, 64> &board) {
		constexpr int dx[] = {1, -1, 0, 0};
		constexpr int dy[] = {0, 0, 1, -1};
		int sum = 0;
		
		for (const auto &sq : board) {
			if (sq.score == -1) {
				u8 x = sq.x;
				u8 y = sq.y;
				for (u8 i = 0; i < 4; ++i) {
					u8 nx = x + dx[i];
					u8 ny = y + dy[i];
					if (nx >= 1 && nx <= 8 && ny >= 1 && ny <= 8) {
						square adjacent = get_square_at(board, nx, ny);
						if (adjacent.score != -1) { sum += adjacent.score; }
					}
				}
			}
		}
		return sum;
	};
	
};

struct knight_moves {
	u8 x;
	u8 y;
	bool altitude;
};

struct computation {
	s64 value;
	char operation;
};

u8 compute_math_steps(std::array<computation, 55> *math_steps, std::array<s32, 11> *known_steps);

bool find_path(std::array<square, 64> *knight_board, 
			   std::array<computation, 55> *math_steps, 
			   u8 k, 
			   std::array<knight_moves, 64> *piece, 
			   int n);

u8 compute_math_steps(std::array<computation, 55> *math_steps, std::array<s32, 11> *known_steps)
{
	s32 score = 0;
	u32 math_walk = 0;
	bool altitude = 1;
	
	u32 math_walk_18 = 0;
	s32 score_18_checkpoint;
	bool altitude_18_checkpoint;
	
	u8 k = 0;
	
	std::bitset<32> part1_bits(math_walk);
	std::bitset<32> part2_bits(math_walk_18);
	
	for (int n = 0; n <= 53; ++n) {
		std::bitset<32> part1_bits(math_walk);
		std::bitset<32> part2_bits(math_walk_18);
		if (n == 0) {
			(*math_steps)[0].value = 0;
		}
		
		else if (n > 0 && n <= 18 && k == 0) {
			if (n % 3 != 0) {
				if (part1_bits[n] == 0) {
					score += n;
					(*math_steps)[n].value = score;
					(*math_steps)[n].operation = '+';
				}
				else if (part1_bits[n] == 1 && altitude == 0) {
					score *= n;
					(*math_steps)[n].value = score;
					(*math_steps)[n].operation = '*';
					altitude = 1;
				}
				else if (part1_bits[n] == 1 && altitude == 1) {
					score /= n;
					(*math_steps)[n].value = score;
					(*math_steps)[n].operation = '/';
					altitude = 0;
				}
			}
			else if (n % 3 == 0) {
				if (part1_bits[n] == 0) {
					score += n;
					(*math_steps)[n].value = score;
					(*math_steps)[n].operation = '+';
				}
				else if (part1_bits[n] == 1 && altitude == 0) {
					score *= n;
					(*math_steps)[n].value = score;
					(*math_steps)[n].operation = '*';
					altitude = 1;
				}
				else if (part1_bits[n] == 1 && altitude == 1) {
					score /= n;
					(*math_steps)[n].value = score;
					(*math_steps)[n].operation = '/';
					altitude = 0;
				}
				
				if (n == 18) {
					score_18_checkpoint = score;
					altitude_18_checkpoint = altitude;
					if (k == 0) { k = 4; }
				}
				
				auto it = std::ranges::find(*known_steps, score);
				if (it == known_steps->end()) {
					//std::cout << "value not found, resetting\n";
					n = -1;
					math_walk += 1;
					score = 0;
					altitude = 1;
				}
				
			}
			//std::cout << "n: " << n 
			//		  << " altitude: " << altitude 
			//		  << " score: " << score 
			//		  << " math_walk: " << math_walk 
			//		  << " part1_bits[n]: " << part1_bits[n] <<"\n";
		}
		
		else if (n >= 18 && k >= 4) {
			if ((n - 18) % k != 0) {
				if (part2_bits[n - 18] == 0) {
					score += n;
					(*math_steps)[n].value = score;
					(*math_steps)[n].operation = '+';
				}
				else if (part2_bits[n - 18] == 1 && altitude == 0) {
					score *= n;
					(*math_steps)[n].value = score;
					(*math_steps)[n].operation = '*';
					altitude = 1;
				}
				else if (part2_bits[n - 18] == 1 && altitude == 1) {
					score /= n;
					(*math_steps)[n].value = score;
					(*math_steps)[n].operation = '/';
					altitude = 0;
				}
			}
			else if ((n - 18) % k == 0) {
				if (part2_bits[n - 18] == 0) {
					score += n;
					(*math_steps)[n].value = score;
					(*math_steps)[n].operation = '+';
				}
				else if (part2_bits[n - 18] == 1 && altitude == 0) {
					score *= n;
					(*math_steps)[n].value = score;
					(*math_steps)[n].operation = '*';
					altitude = 1;
				}
				else if (part2_bits[n - 18] == 1 && altitude == 1) {
					score /= n;
					(*math_steps)[n].value = score;
					(*math_steps)[n].operation = '/';
					altitude = 0;
				}
				auto it = std::ranges::find(*known_steps, score);
				if (it == known_steps->end()) {
					//std::cout << "n: " << n << " k: " << static_cast<int>(k) << "\n";
					n = 18;
					math_walk_18 += 1;
					score = score_18_checkpoint;
					altitude = altitude_18_checkpoint;
					if (math_walk_18 >= 110670) {
						++k;
						math_walk_18 = 0;
					}
				}
			}
			
			//std::cout << "n: " << n 
			//		  << " altitude: " << altitude 
			//		  << " score: " << score 
			//		  << " math_walk_18: " << math_walk_18 
			//		  << " part2_bits[n]: " << part2_bits[n - 18] <<"\n";
		}
		
	}
	std::cout << "math_walk " << math_walk << "\n";
	std::cout << "math_walk_18 " << math_walk_18 << "\n";
	std::cout << "score_18_checkpoint " << score_18_checkpoint << "\n";
	std::cout << "altitude_18_checkpoint " << altitude_18_checkpoint << "\n";
	
	std::cout << "score: " << score << "\n";
	
	return k;
}

bool find_path(std::array<square, 64> *knight_board, 
			   std::array<computation, 55> *math_steps, 
			   u8 k, 
			   std::array<knight_moves, 64> *piece, 
			   int n)
{
	if (n >= 54 && square::do_all_sections_have_towers(*knight_board)) {
		return 1;
	}
	
	if (n == 0) {
		for (auto &square_item : *knight_board) {
			if (!square_item.predetermined_score) {
				square_item.score = -1;
			}
			square_item.has_tower = 0;
		}
			
		square *sq = &square::get_square_at(*knight_board, 1, 1);
		sq->has_tower = 1;
		sq->score = (*math_steps)[n].value;
		square::print_board(*knight_board);
		(*piece)[n] = {1, 1, 1};
		return find_path(knight_board, math_steps, k, piece, n + 1);
	}
	
	else if (n > 0 && n <= 54) {
		(*piece)[n] = (*piece)[n - 1];
		bool divisible = ((n > 0 && n <= 18) && n % 3 == 0) || (n > 18 && (n - 18) % k == 0);
		
		char op = (*math_steps)[n].operation;
		u8 max_moves = (op == '+') ? 8 : 4;
		for (u8 i = 0; i < max_moves; ++i) {
			(*piece)[n] = (*piece)[n - 1];
		
		switch (op) {
			case '+':
				switch (i) {
					case 0: (*piece)[n].x += 1; (*piece)[n].y += 2; /*std::cout << "North North East\n";*/ break;
					case 1: (*piece)[n].x += 2; (*piece)[n].y += 1; /*std::cout << "East North East\n";*/ break;
					case 2: (*piece)[n].x += 2; (*piece)[n].y -= 1; /*std::cout << "East South East\n";*/ break;
					case 3: (*piece)[n].x += 1; (*piece)[n].y -= 2; /*std::cout << "South South East\n";*/ break;
					case 4: (*piece)[n].x -= 1; (*piece)[n].y -= 2; /*std::cout << "South South West\n";*/ break;
					case 5: (*piece)[n].x -= 2; (*piece)[n].y -= 1; /*std::cout << "West South West\n";*/ break;
					case 6: (*piece)[n].x -= 2; (*piece)[n].y += 1; /*std::cout << "West North West\n";*/ break;
					case 7: (*piece)[n].x -= 1; (*piece)[n].y += 2; /*std::cout << "North North West\n";*/ break;
				}
			break;
			
			case '*':
				switch (i) {
					case 0: (*piece)[n].y += 2; (*piece)[n].altitude = 1; /*std::cout << "North\n";*/ break;
					case 1: (*piece)[n].x += 2; (*piece)[n].altitude = 1; /*std::cout << "East\n";*/ break;
					case 2: (*piece)[n].y -= 2; (*piece)[n].altitude = 1; /*std::cout << "South\n";*/ break;
					case 3: (*piece)[n].x -= 2; (*piece)[n].altitude = 1; /*std::cout << "West\n";*/ break;
				}
			break;
			
			case '/':
				switch (i) {
					case 0: (*piece)[n].y += 2; (*piece)[n].altitude = 0; /*std::cout << "North\n";*/ break;
					case 1: (*piece)[n].x += 2; (*piece)[n].altitude = 0; /*std::cout << "East\n";*/ break;
					case 2: (*piece)[n].y -= 2; (*piece)[n].altitude = 0; /*std::cout << "South\n";*/ break;
					case 3: (*piece)[n].x -= 2; (*piece)[n].altitude = 0; /*std::cout << "West\n";*/ break;
				}
			break;
			}
			
			if ((*piece)[n].x > 8 || (*piece)[n].y > 8 || (*piece)[n].x < 1 || (*piece)[n].y < 1) {
				//std::cout << "Out of Bounds\n";
				continue;
			}
			
			square *sq = &square::get_square_at(*knight_board, (*piece)[n].x, (*piece)[n].y);
			
			if ((*piece)[n].altitude == 1 && square::does_section_have_tower(*knight_board, (*piece)[n].x, (*piece)[n].y)) {
				//std::cout << "Altitude is 1 and section " << static_cast<int>(sq->section) << " already has tower\n";
				//square::print_square(*knight_board, (*piece)[n].x, (*piece)[n].y);
				//square::print_board(*knight_board);
				continue;
			}
			
			bool valid_move = 0;
			
			if (!divisible && sq->score == -1) {
				//std::cout << "!divisible && sq->score == -1\n";
				//square::print_square(*knight_board, (*piece)[n].x, (*piece)[n].y);
				//square::print_board(*knight_board);
				sq->score = (*math_steps)[n].value;
				if ((*piece)[n].altitude == 1) { sq->has_tower = 1; }
				valid_move = 1;
			}
			
			if (!divisible && sq->predetermined_score == 1) {
				//std::cout << "Not Divisible and predetermined score\n";
				//square::print_square(*knight_board, (*piece)[n].x, (*piece)[n].y);
				//square::print_board(*knight_board);
				continue;
			}
			
			if (divisible && sq->score == (*math_steps)[n].value) {
				//std::cout << "Divisible, sq->score == (*math_steps)[n].value\n";
				//square::print_square(*knight_board, (*piece)[n].x, (*piece)[n].y);
				//square::print_board(*knight_board);
				if ((*piece)[n].altitude == 1 && sq->predetermined_score == 1) { sq->has_tower = 1; }
				valid_move = 1;
			}
			
			if (divisible && sq->score != (*math_steps)[n].value) {
				//std::cout << "Divisible, sq->score != (*math_steps)[n].value\n";
				//square::print_square(*knight_board, (*piece)[n].x, (*piece)[n].y);
				//square::print_board(*knight_board);
				continue;
			}
			
			if (valid_move) {
				//square::print_board(*knight_board);
				if (find_path(knight_board, math_steps, k, piece, n + 1)) {
					return 1;
				}
				
				if (divisible && sq->predetermined_score == 1 && sq->has_tower == 1) { sq->has_tower = 0; }
				
				if (!divisible && sq->predetermined_score == 0) {
					//std::cout << "Failed path, backtrack\n";
					//square::print_square(*knight_board, (*piece)[n].x, (*piece)[n].y);
					//square::print_board(*knight_board);
					sq->score = -1;
					if (sq->has_tower == 1) { sq->has_tower = 0; }
				}
			}
		}
	}
	return 0;
}

int main()
{
	std::array<computation, 55> math_steps = {{
		{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, 
		{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, 
		{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, 
		{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, 
		{0, 0}, {0, 0}, {0, 0}, {0, 0},
	}};
	
	std::array<s32, 11> known_steps {528, 449, 750, 88, 272, 1, 16, 23, 138, 37, 1100};
	
	u8 k = compute_math_steps(&math_steps, &known_steps);
	std::cout << "k = " << static_cast<int>(k) << "\n";
	std::cout << "math_steps: ";
	math_steps[54].value = 59400; math_steps[54].operation = '*';
	for (int n = 0; n <= 54; ++n) {
		std::cout << "[" << n << "] " << static_cast<int>(math_steps[n].value) 
				  << " " << math_steps[n].operation << "\n";
	}
	
	std::array<square, 64> knight_board = {{
/* ^ */	{-1, 1, 8, 1, 0, 0}, {-1, 2, 8, 1, 0, 0}, {-1, 3, 8, 1, 0, 0}, {-1, 4, 8, 1, 0, 0}, {-1, 5, 8, 1, 0, 0}, {37, 6, 8, 2, 0, 1}, {-1, 7, 8, 2, 0, 0}, {1100, 8, 8, 2, 0, 1},
/* | */	{-1, 1, 7, 3, 0, 0}, {-1, 2, 7, 3, 0, 0}, {-1, 3, 7, 3, 0, 0}, {-1, 4, 7, 4, 0, 0}, {-1, 5, 7, 4, 0, 0}, {-1, 6, 7, 5, 0, 0}, {-1, 7, 7, 5, 0, 0}, {-1, 8, 7, 2, 0, 0},
/* | */	{-1, 1, 6, 3, 0, 0}, {-1, 2, 6, 7, 0, 0}, {-1, 3, 6, 3, 0, 0}, {23, 4, 6, 4, 0, 1}, {-1, 5, 6, 4, 0, 0}, {138, 6, 6, 4, 0, 1}, {-1, 7, 6, 5, 0, 0}, {-1, 8, 6, 2, 0, 0},
/* | */	{528, 1, 5, 6, 0, 1}, {-1, 2, 5, 7, 0, 0}, {-1, 3, 5, 7, 0, 0}, {-1, 4, 5, 8, 0, 0}, {-1, 5, 5, 8, 0, 0}, {-1, 6, 5, 9, 0, 0}, {-1, 7, 5, 5, 0, 0}, {-1, 8, 5, 5, 0, 0},
/* | */	{-1, 1, 4, 6, 0, 0}, {449, 2, 4, 6, 0, 1}, {-1, 3, 4, 7, 0, 0}, {-1, 4, 4, 8, 0, 0}, {16, 5, 4, 8, 0, 1}, {-1, 6, 4, 9, 0, 0}, {-1, 7, 4, 9, 0, 0}, {-1, 8, 4, 13, 0, 0},
/* | */	{-1, 1, 3, 6, 0, 0}, {750, 2, 3, 10, 0, 1}, {-1, 3, 3, 7, 0, 0}, {88, 4, 3, 11, 0, 1}, {-1, 5, 3, 9, 0, 0}, {272, 6, 3, 9, 0, 1}, {1, 7, 3, 12, 0, 1}, {-1, 8, 3, 13, 0, 0},
/* | */	{-1, 1, 2, 6, 0, 0}, {-1, 2, 2, 10, 0, 0}, {-1, 3, 2, 11, 0, 0}, {-1, 4, 2, 11, 0, 0}, {-1, 5, 2, 11, 0, 0}, {-1, 6, 2, 12, 0, 0}, {-1, 7, 2, 12, 0, 0}, {-1, 8, 2, 13, 0, 0},
/* | */	{0, 1, 1, 10, 0, 1}, {-1, 2, 1, 10, 0, 0}, {-1, 3, 1, 10, 0, 0}, {-1, 4, 1, 11, 0, 0}, {-1, 5, 1, 12, 0, 0}, {-1, 6, 1, 12, 0, 0}, {-1, 7, 1, 13, 0, 0}, {-1, 8, 1, 13, 0, 0},
/* Y */	
	 //X -------->
	}};
	
	std::array<knight_moves, 64> piece = {{
		{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, 
		{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, 
		{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, 
		{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, 
		{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, 
		{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, 
		{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, 
		{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0},
	}};
	
	bool truth = find_path(&knight_board, &math_steps, k, &piece, 0);
	std::cout << "\nFound Knight's Path " << truth << "\n";
	
	std::cout << "Final Board\n";
	
	square::print_board(knight_board);
	
	std::cout << "Do all sections have towers? " << (square::do_all_sections_have_towers(knight_board) ? "Yes\n" : "No\n");
	
	std::cout << "Final Answer: " << square::add_neighbor_sums(knight_board) << "\n";
	
	return 0;
}
