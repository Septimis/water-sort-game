#include "Vial.h"

Vial::Vial(unsigned short numSlots, unsigned short index)
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

const unsigned short Vial::getItemDepth() const
{
	std::stack<unsigned short> tempSlots = slots;
	unsigned short itemDepth = 0;
	const unsigned short topItem = tempSlots.top();

	for(unsigned short i = 0; i < tempSlots.size() && topItem == tempSlots.top(); i++)
	{
		itemDepth++;
		tempSlots.pop();
	}

	return itemDepth;
}

void Vial::receive(const unsigned short item)
{
	slots.push(item);
}

const unsigned short Vial::pop()
{
	const unsigned short nextItem = peek();
	slots.pop();
	return nextItem;
}

const bool Vial::isComplete() const
{
	std::stack<unsigned short> temp = slots;
	const unsigned short vialValue = temp.size() ? temp.top() : 0;

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
	return pouringVial.peek() &&									// cannot pour from an empty vial
	(
		!receivingVial.peek() ||									// receiving vial is empty OR
		pouringVial.peek() == receivingVial.peek()					// top two elements match
	) &&
	!pouringVial.isComplete() &&									// don't pour a complete vial
	receivingVial.getFillLevel() != receivingVial.getDepth();	// don't pour into a full vial
}