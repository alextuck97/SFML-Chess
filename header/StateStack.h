#ifndef STATE_STACK_H
#define STATE_STACK_H

#include <functional>
#include <vector>
#include <map>
#include <assert.h>
#include "State.h"

class StateStack
{
public:
	enum Action {
		Push,
		Pop,
		Clear,
	};

public:
	explicit StateStack(State::Context context);

	//Returns a new ptr to a state based off a States::ID key
	//T must inherit from abstract class State
	template<typename T>
	void registerState(States::ID stateID)
	{
		mFactories[stateID] = [this]()
		{
			return State::Ptr(new T(*this, mContext));
		};	
	}

	void update(sf::Time dt);
	void draw();
	void handleEvent(const sf::Event & event);

	void pushState(States::ID stateID);
	void popState();
	void clearStates();

	bool isEmpty() const;

	void setContext(State::Context context) { mContext = context; }

private:
	State::Ptr createState(States::ID stateID);
	void applyPendingChanges();

private:
	struct PendingChange
	{
		PendingChange(Action action, States::ID stateID = States::ID::None);

		Action action;
		States::ID stateID;
	};

private:
	std::vector<State::Ptr> mStack;
	std::vector<PendingChange> mPendingList;
	State::Context mContext;
	std::map<States::ID, std::function<State::Ptr()>> mFactories;


};

#endif