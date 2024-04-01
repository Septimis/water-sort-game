#include "Board.h"
#include <fstream>
#include <iostream>

Vial Board::initializeVial(const std::string a_vialInput, const unsigned short vialIndex)
{
	std::vector<unsigned short> newVialContents;
	std::string currentItem;
	for(const char c : a_vialInput)
	{
		if(c == ',')
		{
			newVialContents.push_back(std::stoi(currentItem));
			currentItem = "";
			continue;
		}

		currentItem = currentItem + c;
	}

	newVialContents.push_back(std::stoi(currentItem));

	Vial newVial(newVialContents.size(), vialIndex);
	for(unsigned short item : newVialContents)
	{
		// don't place 0's in the vial since it means empty
		if(!item)
		{
			continue;
		}

		newVial.receive(item);
	}

	return newVial;
}

Board::Board(char* a_filePath)
{
	std::ifstream levelFile(a_filePath);

	if(levelFile.is_open())
	{
		std::string line;
		unsigned short vialIndex = 0;
		while(std::getline(levelFile, line))
		{
			vials.push_back(initializeVial(line, vialIndex++));
		}
	}

	std::cout << solve(vials);
}

std::string Board::solve(std::vector<Vial> a_vials, std::string previousMove)
{
	if(isBoardSolved(a_vials))
	{
		return previousMove;
	}

	std::string moves = previousMove;

	for(Vial& pouringVial : a_vials)
	{
		for(Vial& receivingVial : a_vials)
		{
			// Don't pour a vial into itself
			if(pouringVial.getIndex() == receivingVial.getIndex())
			{
				continue;
			}

			if(Vial::pour(pouringVial, receivingVial))
			{
				const std::string move = "Pour vial " + std::to_string(pouringVial.getIndex()) + " into vial " + std::to_string(receivingVial.getIndex()) + "\n";
				moves = moves + solve(a_vials, move);
			}
		}
	}

	return moves;
}

void Board::print() const
{
	std::cout << "There are " << vials.size() << " vials\n";
}

const bool Board::isBoardSolved(std::vector<Vial>& a_vials) const
{
	for(const Vial vial : a_vials)
	{
		if(!vial.isComplete())
		{
			return false;
		}
	}

	return true;
}