#include "SlaskEngine.h"
#include <iostream>

using namespace std;

SlaskEngine* SlaskEngine::instance()
{
	static SlaskEngine slaskengine;
	return &slaskengine;
}

SlaskEngine::SlaskEngine()
{
	init();
}

void SlaskEngine::init()
{
	running = true;

	GraphicsHandler* graphics = GraphicsHandler::instance();
	graphics->init(1280, 720, "SlaskEngine");

	InputHandler* input = InputHandler::instance();
	input->init();
	AudioHandler* audio = AudioHandler::instance();
	audio->init(24);
	Sprite testS("slask.png");
	Font testF("Progandae.otf");

	/*TESTING INIT*/
	FMOD_RESULT result;

	FMOD::Studio::Bank* masterBank = NULL;
	result = audio->getSystem()->loadBankFile("fmod/TestBank/Build/Desktop/Master Bank.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &masterBank);
	if (result != FMOD_OK)
		cout << "Loading master bank: " << FMOD_ErrorString(result) << '\n';

	FMOD::Studio::Bank* stringsBank = NULL;
	result = audio->getSystem()->loadBankFile("fmod/TestBank/Build/Desktop/Master Bank.strings.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &stringsBank);
	if (result != FMOD_OK)
		cout << "Loading master strings bank: " << FMOD_ErrorString(result) << '\n';

	//should only be event:/Music
	FMOD::Studio::EventDescription* spoop = NULL;
	result = audio->getSystem()->getEvent("event:/Music", &spoop);
	if (result != FMOD_OK)
		cout << "Getting event: " << FMOD_ErrorString(result) << '\n';

	result = spoop->loadSampleData();
	if (result != FMOD_OK)
		cout << "Load Sample Data: " << FMOD_ErrorString(result) << '\n';

	FMOD::Studio::EventInstance* eventInstance = NULL;
	result = spoop->createInstance(&eventInstance);
	if (result != FMOD_OK)
		cout << "Creating instance: " << FMOD_ErrorString(result) << '\n';

	result = eventInstance->setVolume(1);
	if (result != FMOD_OK)
		cout << "Volume: " << FMOD_ErrorString(result) << '\n';


	while (running)
	{
		if (input->run())
			running = false;
		

		/*TESTING GAME CODE*/
		{
			if (input->getkey(InputHandler::Space) == 1)
			{
				eventInstance->start();
				if (result != FMOD_OK)
					cout << "Playing: " << FMOD_ErrorString(result) << '\n';
			}
			if (input->getkey(InputHandler::Return) == 1)
			{
				eventInstance->stop(FMOD_STUDIO_STOP_IMMEDIATE);
				if (result != FMOD_OK)
					cout << "Stopping: " << FMOD_ErrorString(result) << '\n';
			}
		}

		//update??

		result = audio->getSystem()->update();
		if (result != FMOD_OK)
			cout << "Update: " << FMOD_ErrorString(result) << '\n';


		graphics->drawBegin();

		/*TESTING DRAWING*/
		{
			graphics->drawSprite(&testS, 0, 0, 100, 100);
		}

		graphics->drawEnd();

	}

	graphics->close();

	//what is this? Kappa
	//IDK I tried to play sounds
	//&FMOD::Studio::Bank::unloadSampleData;

}

SlaskEngine::~SlaskEngine()
{
}