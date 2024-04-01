#pragma once
#include <vector>
#include <string>
#include "Vial.h"

class Board
{
public:
	Board(char* a_filePath);

	void print() const;

private:
	std::vector<Vial> vials;

	std::string solve(std::vector<Vial> a_vials, std::string previousMove = "");

	// Helper function to initialize a vial
	Vial initializeVial(const std::string a_vialInput, const unsigned short vialIndex);

	const bool isBoardSolved(std::vector<Vial>& a_vials) const;
};