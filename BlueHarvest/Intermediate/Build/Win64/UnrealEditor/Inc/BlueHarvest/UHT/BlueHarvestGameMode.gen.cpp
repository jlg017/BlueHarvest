// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "BlueHarvest/BlueHarvestGameMode.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeBlueHarvestGameMode() {}
// Cross Module References
	BLUEHARVEST_API UClass* Z_Construct_UClass_ABlueHarvestGameMode();
	BLUEHARVEST_API UClass* Z_Construct_UClass_ABlueHarvestGameMode_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	UPackage* Z_Construct_UPackage__Script_BlueHarvest();
// End Cross Module References
	void ABlueHarvestGameMode::StaticRegisterNativesABlueHarvestGameMode()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ABlueHarvestGameMode);
	UClass* Z_Construct_UClass_ABlueHarvestGameMode_NoRegister()
	{
		return ABlueHarvestGameMode::StaticClass();
	}
	struct Z_Construct_UClass_ABlueHarvestGameMode_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ABlueHarvestGameMode_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameModeBase,
		(UObject* (*)())Z_Construct_UPackage__Script_BlueHarvest,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ABlueHarvestGameMode_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ABlueHarvestGameMode_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "BlueHarvestGameMode.h" },
		{ "ModuleRelativePath", "BlueHarvestGameMode.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ABlueHarvestGameMode_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ABlueHarvestGameMode>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_ABlueHarvestGameMode_Statics::ClassParams = {
		&ABlueHarvestGameMode::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x008802ACu,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ABlueHarvestGameMode_Statics::Class_MetaDataParams), Z_Construct_UClass_ABlueHarvestGameMode_Statics::Class_MetaDataParams)
	};
	UClass* Z_Construct_UClass_ABlueHarvestGameMode()
	{
		if (!Z_Registration_Info_UClass_ABlueHarvestGameMode.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ABlueHarvestGameMode.OuterSingleton, Z_Construct_UClass_ABlueHarvestGameMode_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_ABlueHarvestGameMode.OuterSingleton;
	}
	template<> BLUEHARVEST_API UClass* StaticClass<ABlueHarvestGameMode>()
	{
		return ABlueHarvestGameMode::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(ABlueHarvestGameMode);
	ABlueHarvestGameMode::~ABlueHarvestGameMode() {}
	struct Z_CompiledInDeferFile_FID_UnrealProjects_BlueHarvest_BlueHarvest_Source_BlueHarvest_BlueHarvestGameMode_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_UnrealProjects_BlueHarvest_BlueHarvest_Source_BlueHarvest_BlueHarvestGameMode_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_ABlueHarvestGameMode, ABlueHarvestGameMode::StaticClass, TEXT("ABlueHarvestGameMode"), &Z_Registration_Info_UClass_ABlueHarvestGameMode, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ABlueHarvestGameMode), 1127110733U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_UnrealProjects_BlueHarvest_BlueHarvest_Source_BlueHarvest_BlueHarvestGameMode_h_56902248(TEXT("/Script/BlueHarvest"),
		Z_CompiledInDeferFile_FID_UnrealProjects_BlueHarvest_BlueHarvest_Source_BlueHarvest_BlueHarvestGameMode_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_UnrealProjects_BlueHarvest_BlueHarvest_Source_BlueHarvest_BlueHarvestGameMode_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
