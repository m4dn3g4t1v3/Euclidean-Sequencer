/*
  ==============================================================================

    EuclideanRythmComponent.cpp
    Created: 31 Mar 2022 6:32:07pm
    Author:  dburgos

  ==============================================================================
*/

#include <JuceHeader.h>
#include "EuclideanRythmComponent.h"

//==============================================================================
// funciones by default del component
//==============================================================================

EuclideanRythmComponent::EuclideanRythmComponent()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    this->_euclideanRythm = { NULL };
    this->_steps = 0;
    this->_events = 0;
    this->_rotation = 0;
    _euclideanRythm[0] = 0;
}

EuclideanRythmComponent::EuclideanRythmComponent(int steps, int events, int rotation) {
    setEuclideanRythm(steps, events, rotation);
}

EuclideanRythmComponent::~EuclideanRythmComponent()
{
}

void EuclideanRythmComponent::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

}

void EuclideanRythmComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}


//==============================================================================
// getters and setters
//==============================================================================

int EuclideanRythmComponent::getSteps() {
    return this->_steps;
}

int EuclideanRythmComponent::getEvents() {
    return this->_events;
}

vector<int> EuclideanRythmComponent::getEuclideanRythm() {
    return _euclideanRythm;
}

juce::String EuclideanRythmComponent::getList() {
    juce::String ret;
    vector<int>::iterator it = this->_euclideanRythm.begin();
    for (it = this->_euclideanRythm.begin(); it != this->_euclideanRythm.end(); ++it)
        ret += (*it);
    return ret;
}

void EuclideanRythmComponent::setEuclideanRythm(int steps, int events, int rotation) {

    this->_euclideanRythm.clear();

    this->_steps = steps;
    this->_events = events;

    if (events == 0) {
        for (int i = 0; i < this->_steps; i++)
            this->_euclideanRythm.push_back(0);
        rotateRight(rotation);
        return;
    }

    int previous = 0;
    this->_euclideanRythm.push_back(1);

    for (int i = 1; i < steps; i++) {
        int currentValue = floor(((double)events / steps) * i);
        if (currentValue == previous)
            this->_euclideanRythm.push_back(0);
        else
            this->_euclideanRythm.push_back(1);
        previous = currentValue;
    }
    rotateRight(rotation);
}

void EuclideanRythmComponent::setEvents(int newEvents) {
    setEuclideanRythm(this->_steps, newEvents, _rotation);
}

void EuclideanRythmComponent::setSteps(int newSteps) {
    setEuclideanRythm(newSteps, this->_events, _rotation);
}

//==============================================================================
// other aux functions
//==============================================================================

void EuclideanRythmComponent::rotateRight(int times) {
    for (int i = 0; i < times; i++) {
        int last = this->_euclideanRythm.back();
        vector<int>::iterator it = this->_euclideanRythm.begin();
        this->_euclideanRythm.insert(it, last);
        this->_euclideanRythm.pop_back();
    }
    this->_rotation += times;
}

void EuclideanRythmComponent::rotateLeft(int times) {
    for (int i = 0; i < times; i++) {
        int first = this->_euclideanRythm.front();
        this->_euclideanRythm.push_back(first);
        this->_euclideanRythm.erase(this->_euclideanRythm.begin());
    }
    this->_rotation -= times;
}

void EuclideanRythmComponent::showList() {
    vector<int>::iterator it = this->_euclideanRythm.begin();
    for (it = this->_euclideanRythm.begin(); it != this->_euclideanRythm.end(); ++it)
        cout << *it << " ";
    cout << endl << endl;
}

