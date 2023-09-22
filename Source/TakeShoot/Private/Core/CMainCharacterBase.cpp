// Fill out your copyright notice in the Description page of Project Settings.


#include "..\..\Public\Core\CMainCharacterBase.h"
#include "Camera/CameraComponent.h"
#include "Components/ChildActorComponent.h"
#include "GameFramework/CharacterMovementComponent.h"



// Sets default values
ACMainCharacterBase::ACMainCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create Cameraref
	FPSCameraComponenet = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	check(FPSCameraComponenet != nullptr)

	FPSSpringArmComponenet = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	check(FPSCameraComponenet != nullptr)

	//Create Child Actor Sword
	Weapon = CreateDefaultSubobject<UChildActorComponent>(TEXT("Sword"));
	Weapon->SetupAttachment(GetMesh(),"hand_rSocket");
	Weapon->SetVisibility(false);

	//Setup Attachment SpringArm
	FPSSpringArmComponenet->SetupAttachment(CastChecked<UMeshComponent>(GetMesh()));
	FPSSpringArmComponenet->SetRelativeLocation(FVector(0.0f,0.0f,170.0f));
	FPSSpringArmComponenet->bUsePawnControlRotation = true;

	//Setup Attachment Camera
	FPSCameraComponenet->SetupAttachment(FPSSpringArmComponenet);
	
}

// Called when the game starts or when spawned
void ACMainCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	//Run Speed
	RunSpeed = 1200;
	WalkSpeed = 600;
	WeaponWalkSpeed = 500;
}

// Called every frame
void ACMainCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ACMainCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	PlayerInputComponent->BindAxis("Move Forward",this,&ACMainCharacterBase::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACMainCharacterBase::MoveRight);
	PlayerInputComponent->BindAxis("Turn",this,&ACMainCharacterBase::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp",this,&ACMainCharacterBase::AddControllerPitchInput);
	PlayerInputComponent->BindAction("Jump",IE_Pressed,this,&ACMainCharacterBase::StartJump);
	PlayerInputComponent->BindAction("Jump",IE_Released,this,&ACMainCharacterBase::StopJumping);
	PlayerInputComponent->BindAction("Crouch",IE_Pressed,this,&ACMainCharacterBase::StartCrouch);
	PlayerInputComponent->BindAction("Crouch",IE_Released,this,&ACMainCharacterBase::StopCrouch);
	PlayerInputComponent->BindAction("Run",IE_Pressed,this,&ACMainCharacterBase::StartRun);
	PlayerInputComponent->BindAction("Run",IE_Released,this,&ACMainCharacterBase::StopRun);

	//Weapon Inputs
	PlayerInputComponent->BindAction("Take FreeHand",IE_Pressed,this,&ACMainCharacterBase::TakeFreehand);
	PlayerInputComponent->BindAction("Take Sword",IE_Pressed,this,&ACMainCharacterBase::TakeSword);
}

void ACMainCharacterBase::MoveForward(float Value)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, Value);
}

void ACMainCharacterBase::MoveRight(float Value)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction,Value);
}

void ACMainCharacterBase::StartJump()
{
	bPressedJump = true;
}

void ACMainCharacterBase::StopJump()
{
	bPressedJump = false;
}

void ACMainCharacterBase::StartCrouch()
{
	bIsCrouched = true;
}

void ACMainCharacterBase::StopCrouch()
{
	bIsCrouched = false;
}

void ACMainCharacterBase::StartRun()
{
	if (CurrentWeapon == CurrentWeapon::E_FreeHand)
	{
		//FreeHand Walk Speed
		GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
	}
	else
	{
		//With weapon Walk Speed
		GetCharacterMovement()->MaxWalkSpeed = WeaponWalkSpeed;
	}
}

void ACMainCharacterBase::StopRun()
{
	if (CurrentWeapon == CurrentWeapon::E_FreeHand)
	{
		//FreeHand Walk Speed
		GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	}
	else
	{
		//With weapon Walk Speed
		GetCharacterMovement()->MaxWalkSpeed = WeaponWalkSpeed;
	}
}

void ACMainCharacterBase::TakeFreehand()
{
	CurrentWeapon = CurrentWeapon::E_FreeHand;
	Weapon->SetVisibility(false);
}

void ACMainCharacterBase::TakeSword()
{
	CurrentWeapon = CurrentWeapon::E_Sword;
	StopRun();
	Weapon->SetVisibility(true);
}


