#include "..\header\StateStack.h"

StateStack::StateStack(State::Context context) : mContext(context)
{

}

//Return a unique_ptr to a state
State::Ptr StateStack::createState(States::ID stateID)
{
	auto found = mFactories.find(stateID);
	assert(found != mFactories.end());
		
	return found->second();
}

//Handle events from the top state to the bottom state.
void StateStack::handleEvent(const sf::Event & event)
{
	for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr)
	{
		if (!(*itr)->handleEvent(event))//Allows states to determine how far down a command will go
			return;
	}

	applyPendingChanges();
}

//Update application from all states until an update function returns false
void StateStack::update(sf::Time dt)
{
	for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr)
	{
		if (!(*itr)->update(dt))
			return;
	}

	applyPendingChanges();
}

//Draws from bottom up so most recent things drawn last
void StateStack::draw()
{
	for (auto & state : mStack)
		state->draw();
}

//Change states based on what is in the mPendingChanges list
void StateStack::applyPendingChanges()
{
	for (PendingChange change : mPendingList)
	{
		switch (change.action)
		{
		case Push:
			mStack.push_back(createState(change.stateID));
			break;

		case Pop:
			mStack.pop_back();
			break;

		case Clear:
			mStack.clear();
			break;
		}
	}

	mPendingList.clear();
}


//Push a state to the stack
void StateStack::pushState(States::ID stateID)
{
	mPendingList.push_back(PendingChange(Push, stateID));
}

//Pop a state from the stack
void StateStack::popState()
{
	mPendingList.push_back(PendingChange(Pop));
}

//Clear all states
void StateStack::clearStates()
{
	mPendingList.push_back(PendingChange(Clear));
}


bool StateStack::isEmpty() const
{
	return mStack.empty();
}


StateStack::PendingChange::PendingChange(Action action, States::ID StateID) : action(action), stateID(StateID)
{

}