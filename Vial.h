#pragma once
#include <stack>

#define uint8 unsigned char

class Vial
{
public:
	Vial(uint8 numSlots, uint8 index);
	const uint8 getIndex() const { return this->index; }

	/**
	 * Pours this current vial into the passed in vial
	 * 
	 * @arg pouringVial - the vial doing the pouring
	 * @arg receivingVial - the vial receiving
	 * 
	 * @return if the pour was successful
	 */ 
	static bool pour(Vial& pouringVial, Vial& receivingVial);

	// Gets the total depth of the vial
	const uint8 getDepth() const { return numSlots; }

	// Gets how many slots the top item takes without interuption
	const uint8 getItemDepth() const;

	void receive(const uint8 item);

	// reports if the vial eligible for a winning level
	const bool isComplete() const;
	const bool isEmpty() const { return slots.empty(); };

	// returns top item in the vial or 0 if empty
	const uint8 peek() const { return slots.empty() ? 0 : slots.top(); }
	const uint8 pop();

	uint8 getFillLevel() const { return slots.size(); }
	uint8 getNumAvailableSlots() const { return numSlots - slots.size(); }

private:
	std::stack<uint8> slots;
	uint8 numSlots = 0;
	uint8 index = 0;

	static bool canPour(Vial pouringVial, Vial receivingVial);
};

#undef uint8