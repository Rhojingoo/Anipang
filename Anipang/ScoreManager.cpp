#include "ScoreManager.h"
#include "Number.h"

ScoreManager::ScoreManager()
{
}

ScoreManager::~ScoreManager()
{
}

void ScoreManager::BeginPlay()
{
	AActor::BeginPlay();
	Units = GetWorld()->SpawnActor<ANumber>();
	Units->SetActorLocation({ 240,50 });
	Units->SetNumScale(55, 55);
}

void ScoreManager::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	if (Score < 10)
	{
		Units->SetNumber(Score);
	}
	else if (Score >= 100)
	{
		if (Hunders == nullptr)
		{
			Hunders = GetWorld()->SpawnActor<ANumber>();
			Hunders->SetNumScale(55, 55);
			Hunders->SetNumber(1);
			Hunders->SetActorLocation({ 210,50 });
			Tens->SetActorLocation({ 240,50 });
			Units->SetActorLocation({ 270,50 });
		}

		int NumHundress = Score / 100;
		int Numtens = (Score - (NumHundress * 100)) / 10;
		int Numunits = Score % 10;
		Hunders->SetNumber(NumHundress);
		Units->SetNumber(Numunits);
		Tens->SetNumber(Numtens);
	}
	else if (Score >= 10)
	{
		if(Tens == nullptr)
		{
			Tens = GetWorld()->SpawnActor<ANumber>();
			Tens->SetActorLocation({ 225,50 });
			Tens->SetNumScale(55, 55);
			Tens->SetNumber(1);
			Units->SetActorLocation({ 255,50 });
		}

		int Numtens = Score / 10;
		int Numunits = Score % 10;
		Units->SetNumber(Numunits);
		Tens->SetNumber(Numtens);
	}

	else if (Score >= 1000)
	{

	}
	else if (Score >= 10000)
	{

	}

}
