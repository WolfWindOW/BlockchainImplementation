// 
// Block.cpp
// Blockguard
//
// Noah Wyborny
// 6/6/2021
//


#include "Block.hpp"
#include <random>
/*
 {
	return (rand() % MAX_SIZE + 1);
}
*/
uint32_t CBlock::computeHash() const {
	std::random_device device;
	std::mt19937 rng(device());
	std::uniform_int_distribution<uint32_t> distribution(1, MAX_SIZE);
	return distribution(rng);
}
