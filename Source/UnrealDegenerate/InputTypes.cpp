// Fill out your copyright notice in the Description page of Project Settings.


#include "InputTypes.h"

bool FPlayerInputPacket::ShouldBeProcessed()
{
	return InputPattern > 0;
}