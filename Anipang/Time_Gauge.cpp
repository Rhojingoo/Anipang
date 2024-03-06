#include "Time_Gauge.h"
#include "Number.h"

ATime_Gauge::ATime_Gauge()
{
}

ATime_Gauge::~ATime_Gauge()
{
}

void ATime_Gauge::BeginPlay()
{
	Renderer = CreateImageRenderer(5);
	Renderer->SetImage("TimeGauge");
	Renderer->CreateAnimation("Nomarl", "TimeGauge", 0, 0, 0.1f, true);
	Renderer->CreateAnimation("Hurry", "TimeGauge", 1, 1, 0.1f, true);
	Renderer->SetTransform({ {0.f,0.f}, {Size, 30.f} });	
	//Renderer->SetImageCuttingTransform({ {0,0}, {410, 29} });
	Renderer->ChangeAnimation("Nomarl");
	//Renderer->SetImage("UnderBarUI2.png");
}

void ATime_Gauge::Tick(float _DeltaTime)
{
	Pos = GetActorLocation();

	if (Start == true)
	{
		if (NumCreate == false)
		{
			Tens = GetWorld()->SpawnActor<ANumber>();
			Tens->SetNumber(6);
			Tens->SetActorLocation({ 224 ,705 });
			Tens->SetNumScale(25, 25);

			Units = GetWorld()->SpawnActor<ANumber>();
			Units->SetNumber(0);
			Units->SetActorLocation({ 241 ,705 });
			Units->SetNumScale(25, 25);
			NumCreate = true;
		}

		if (Test_BlockMove_Mode == false && TimeStop == false)
		{
			Time -= _DeltaTime;
			float checktime = PreveTime - Time;
			if (checktime >= 1.f)
			{
				PreveTime = Time;
				float SumTotalSize = (TotalSize - (TotalSize * (Time / TotalTime)));
				float SumChangeSize = (Size - (TotalSize * (Time / TotalTime)));
				Size = TotalSize - SumTotalSize;
				Renderer->SetScale({ Size, 30.f });
				Pos.X = Pos.X - SumChangeSize / 2;
				SetActorLocation(Pos);
			}

			{
				int Num_Units = static_cast<int>(Time) % 10;
				Units->SetNumber(Num_Units);
				int Num_Tens = static_cast<int>(Time) / 10;
				Tens->SetNumber(Num_Tens);
			}

			if (Time < 10.f)
			{
				if (Hurry == false)
				{
					Renderer->ChangeAnimation("Hurry");
					Hurry = true;
				}
			}

			if (Time <= 0.f)
			{
				Finish = true;
			}
		}
	}
}
