#include "State.h"

SDL_Renderer* State::renderer{};
StateEnum State::currentState = TITLE;
StateEnum State::nextState = NONE;

void State::setRenderer(SDL_Renderer *r)
{
	renderer = r;
}

void State::setCurrentState(StateEnum arg)
{
	currentState = arg;
}

void State::setNextState(StateEnum arg)
{
	nextState = arg;
}

StateEnum State::getCurrentState()
{
	return currentState;
}

StateEnum State::getNextState()
{
	return nextState;
}