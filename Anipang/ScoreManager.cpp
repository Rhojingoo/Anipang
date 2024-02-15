#include "ScoreManager.h"
#include "Number.h"


int ScoreManager::Score = 0;
bool ScoreManager::Restart= false;

ScoreManager::ScoreManager()
{
}

ScoreManager::~ScoreManager()
{
}



void ScoreManager::BeginPlay()
{
	AActor::BeginPlay();

	if (ScoreLevel_Use == false)
	{
		Units = GetWorld()->SpawnActor<ANumber>();
		Units->SetActorLocation({ 240,50 });
		Units->SetNumScale(55, 55);
	}
}

void ScoreManager::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	if (ScoreLevel_Use == true)
	{
		if (Units == nullptr)
		{
			Units = GetWorld()->SpawnActor<ANumber>();
			Units->SetActorLocation({ 240,200 });
			Units->SetNumScale(55, 55);
		}

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
				Hunders->SetActorLocation({ 210,200 });
				Tens = GetWorld()->SpawnActor<ANumber>();
				Tens->SetActorLocation({ 240,200 });
				Tens->SetNumScale(55, 55);
				Tens->SetNumber(1);
				Units->SetActorLocation({ 270,200 });
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
			if (Tens == nullptr)
			{
				Tens = GetWorld()->SpawnActor<ANumber>();
				Tens->SetActorLocation({ 225,200 });
				Tens->SetNumScale(55, 55);
				Tens->SetNumber(1);
				Units->SetActorLocation({ 255,200 });
			}

			int Numtens = Score / 10;
			int Numunits = Score % 10;
			Units->SetNumber(Numunits);
			Tens->SetNumber(Numtens);
		}

	}
	else
	{
		if (Restart == true)
		{
			if (Score == 0)
			{
				if (Thousions != nullptr)
				{
					Thousions->Destroy(0.f);
					Thousions = nullptr;
				}
				if (Hunders != nullptr)
				{
					Hunders ->Destroy(0.f);
					Hunders = nullptr;
				}
				if (Tens != nullptr)
				{
					Tens->Destroy(0.f);
					Tens = nullptr;
				}
				Units->SetNumber(Score);
				Units->SetActorLocation({ 240,50 });
			}
			Restart = false;
		}
		else
		{
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
				if (Tens == nullptr)
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
		
	}

}
