#include <Samples.hpp>

using namespace std;

Samples::Samples(void)
{
	this->samplesA.assign(1500,0);
	this->samplesB.assign(1500,0);
	this->delayA = 500;
	this->delayB = 500;
}

vector<int> Samples::getSamplesA(void)
{
	return this->samplesA;
}

vector<int> Samples::getSamplesB(void)
{
	return this->samplesB;
}

int Samples::getDelayA(void)
{
	return this->delayA;
}

int Samples::getDelayB(void)
{
	return this->delayB;
}
