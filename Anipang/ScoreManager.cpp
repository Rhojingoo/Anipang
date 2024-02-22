#include "ScoreManager.h"
#include "Number.h"


int ScoreManager::Score = 0;
bool ScoreManager::Restart = false;

ScoreManager::ScoreManager()
{
}

ScoreManager::~ScoreManager()
{
}

void ScoreManager::SetFont()
{
	Text = std::to_string(Score);
	Renderer->SetText(Text);
}

void ScoreManager::ScoreImageRender()
{
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
		else if (Score >= 1000)
		{
			if (Thousions == nullptr)
			{
				Thousions = GetWorld()->SpawnActor<ANumber>();
				Thousions->SetNumScale(55, 55);
				Thousions->SetNumber(1);
				Thousions->SetActorLocation({ 195,200 });
			}
			if (Hunders == nullptr)
			{
				Hunders = GetWorld()->SpawnActor<ANumber>();
				Hunders->SetNumScale(55, 55);
				Hunders->SetNumber(1);
				Hunders->SetActorLocation({ 225,200 });
			}
			if (Tens == nullptr)
			{
				Tens = GetWorld()->SpawnActor<ANumber>();
				Tens->SetActorLocation({ 240,200 });
				Tens->SetNumScale(55, 55);
				Tens->SetActorLocation({ 255,200 });
				Units->SetActorLocation({ 285,200 });
			}
			int NumThousions = Score / 1000;
			int NumHundress = (Score - (NumThousions * 1000)) / 100;
			int Numtens = (Score - (NumThousions * 1000) - (NumHundress * 100)) / 10;
			int Numunits = Score % 10;
			Thousions->SetNumber(NumThousions);
			Hunders->SetNumber(NumHundress);
			Units->SetNumber(Numunits);
			Tens->SetNumber(Numtens);
		}
		else if (Score >= 100)
		{
			if (Hunders == nullptr)
			{
				Hunders = GetWorld()->SpawnActor<ANumber>();
				Hunders->SetNumScale(55, 55);
				Hunders->SetNumber(1);
				Hunders->SetActorLocation({ 210,200 });
			}
			if (Tens == nullptr)
			{
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
					Hunders->Destroy(0.f);
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
			else if (Score >= 1000)
			{
				if (Thousions == nullptr)
				{
					Thousions = GetWorld()->SpawnActor<ANumber>();
					Thousions->SetNumScale(55, 55);
					Thousions->SetNumber(1);
					Thousions->SetActorLocation({ 195,50 });
				}
				if (Hunders == nullptr)
				{
					Hunders = GetWorld()->SpawnActor<ANumber>();
					Hunders->SetNumScale(55, 55);
					Hunders->SetNumber(1);
					Hunders->SetActorLocation({ 225,50 });
				}
				if (Tens == nullptr)
				{
					Tens = GetWorld()->SpawnActor<ANumber>();
					Tens->SetNumScale(55, 55);
					Hunders->SetNumber(1);
					Tens->SetActorLocation({ 255,50 });
					Units->SetActorLocation({ 285,50 });
				}
				int NumThousions = Score / 1000;
				int NumHundress = (Score - (NumThousions * 1000)) / 100;
				int Numtens = (Score - (NumThousions * 1000) - (NumHundress * 100)) / 10;
				int Numunits = Score % 10;
				Thousions->SetNumber(NumThousions);
				Hunders->SetNumber(NumHundress);
				Units->SetNumber(Numunits);
				Tens->SetNumber(Numtens);
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
				if (Tens == nullptr)
				{
					Tens = GetWorld()->SpawnActor<ANumber>();
					Tens->SetNumScale(55, 55);
					Tens->SetNumber(1);
					Tens->SetActorLocation({ 240,50 });
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


			else if (Score >= 10000)
			{

			}
		}

	}
}

void ScoreManager::BeginPlay()
{
	AActor::BeginPlay();

	Renderer = CreateImageRenderer(100);
	Text = std::to_string(Score);
	Renderer->SetText(Text);
	Renderer->SetTextSize(45);
	Renderer->SetTextColor(Color8Bit::Black, Color8Bit::White);
	Renderer->SwitchTextBold();
	SetActorLocation({ 240,60 });
	/*if (ScoreLevel_Use == false)
	{
		Units = GetWorld()->SpawnActor<ANumber>();
		Units->SetActorLocation({ 240,50 });
		Units->SetNumScale(55, 55);
	}*/
}

void ScoreManager::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	
	if (ScoreLevel_Use == true)
	{
		SetActorLocation({ 240,200 });
	}
	Text = std::to_string(Score);
	Renderer->SetText(Text);

	//ScoreImageRender();
}
