#include "Vial.h"

#define uint8 unsigned char

Vial::Vial(uint8 numSlots, uint8 index)
{
	this->numSlots = numSlots;
	this->index = index;
}

bool Vial::pour(Vial& pouringVial, Vial& receivingVial)
{
	// return early if we can't pour
	if(!Vial::canPour(pouringVial, receivingVial))
	{
		return false;
	}

	while(Vial::canPour(pouringVial, receivingVial))
	{
		receivingVial.receive(pouringVial.pop());
	}

	return true;
}

const uint8 Vial::getItemDepth() const
{
	std::stack<uint8> tempSlots = slots;
	uint8 itemDepth = 0;
	const uint8 topItem = tempSlots.top();

	for(uint8 i = 0; i < tempSlots.size() && topItem == tempSlots.top(); i++)
	{
		itemDepth++;
		tempSlots.pop();
	}

	return itemDepth;
}

void Vial::receive(const uint8 item)
{
	slots.push(item);
}

const uint8 Vial::pop()
{
	const uint8 nextItem = peek();
	slots.pop();
	return nextItem;
}

const bool Vial::isComplete() const
{
	std::stack<uint8> temp = slots;
	const uint8 vialValue = temp.size() ? temp.top() : 0;

	bool isComplete = true;
	
	while(!temp.empty())
	{
		if(temp.top() != vialValue)
		{
			isComplete = false;
		}

		temp.pop();
	}

	if(slots.size() != numSlots && slots.size())
	{
		isComplete = false;
	}

	return isComplete;
}

bool Vial::canPour(Vial pouringVial, Vial receivingVial)
{
	return
	pouringVial.getIndex() != receivingVial.getIndex() && 		// Cannot pour a vial into itself
	pouringVial.peek() &&										// cannot pour from an empty vial
	(															// Elements match
		!receivingVial.peek() ||									// receiving vial is empty OR
		pouringVial.peek() == receivingVial.peek()					// top two elements match
	) &&
	!(															// Don't pour if
		pouringVial.getItemDepth() == pouringVial.getDepth() &&		// The pouring vial has only one uniform color &
		receivingVial.isEmpty()										// The receiving vial is empty.
	) &&
	!pouringVial.isComplete() &&								// don't pour a completed vial
	receivingVial.getFillLevel() != receivingVial.getDepth();	// don't pour into a full vial
}

#undef uint8