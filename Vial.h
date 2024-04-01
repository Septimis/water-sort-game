#pragma once
#include <stack>

class Vial
{
public:
	Vial(unsigned short numSlots, unsigned short index);
	const unsigned short getIndex() const { return this->index; }

	/**
	 * Pours this current vial into the passed in vial
	 * 
	 * @arg pouringVial - the vial doing the pouring
	 * @arg receivingVial - the vial receiving
	 * 
	 * @return if the pour was successful
	 */ 
	static bool pour(Vial& pouringVial, Vial& receivingVial);

	const unsigned short getNumSlots() const { return numSlots; }

	void receive(const unsigned short item);

	// reports if the vial eligible for a winning level
	const bool isComplete() const;

	// returns top item in the vial or 0 if empty
	const unsigned short peek() const { return slots.empty() ? 0 : slots.top(); }

	const unsigned short pop();
	std::size_t getFillLevel() const { return slots.size(); }

private:
	std::stack<unsigned short> slots;
	unsigned short numSlots = 0;
	unsigned short index = 0;

	static bool canPour(Vial pouringVial, Vial receivingVial);
};