#include <CommonAPI/Runtime.h>
#include "includes/Interfaces/TunerAdditionalServiceIndividualStub.h"
#include "includes/Interfaces/TunerStationIndividualStub.h"
#include "includes/Interfaces/TunerConfigurationIndividualStub.h"

int main( int argc, char *argv[] )
{
	std::shared_ptr<CommonAPI::Factory> factory;
	std::shared_ptr<CommonAPI::Factory> factory2;
	std::shared_ptr<CommonAPI::Factory> factory3;
	std::shared_ptr<CommonAPI::Runtime> runtime;
	cout << "Welcome to Genivi Tuner API simulation (Tuner Middleware part) " << endl << endl;
	runtime  = CommonAPI::Runtime::load();
	factory  = runtime->createFactory();
	factory2 = runtime->createFactory();
	factory3 = runtime->createFactory();
	bool registerResult;
	//register Interface for Tuner Station Management
	auto m_stationStub = std::make_shared<TunerStationIndividualStub>();
	registerResult = factory->registerService(m_stationStub, "local:TunerStation.TunerStation:TunerStation.Instance1");
	if (registerResult != true) {
		cerr << "Registering of TunerStation stub failed." << endl;
		exit(1);
	}
	cout << "Successfully registered TunerStation stub." << endl;
	//register Interface for Tuner Additional Services
	auto m_additionalServiceStub = std::make_shared<TunerAdditionalServiceIndividualStub>();//this);
	registerResult = factory2->registerService(m_additionalServiceStub, "local:TunerAdditionalService.TunerAdditionalService:TunerAdditionalService.Instance2");
	if (registerResult != true) {
		cerr << "Registering of TunerAdditionalService stub failed." << endl;
		exit(1);
	}
	cout << "Successfully registered TunerAdditionalService stub." << endl;

	//register Interface for Tuner Additional Services
	auto m_configurationServiceStub = std::make_shared<TunerConfigurationIndividualStub>();
	registerResult = factory3->registerService(m_configurationServiceStub, "local:TunerConfiguration.TunerConfiguration:TunerConfiguration.Instance3");
	if (registerResult != true) {
		cerr << "Registering of TunerConfiguration stub failed." << endl;
		exit(1);
	}
	cout << "Successfully registered TunerConfiguration stub." << endl;
	Middleware *middleware = new Middleware();
	m_stationStub          		->setMiddleware(middleware);
	m_additionalServiceStub		->setMiddleware(middleware);
	m_configurationServiceStub	->setMiddleware(middleware);
	middleware->runLoop();
	return 0;
}
