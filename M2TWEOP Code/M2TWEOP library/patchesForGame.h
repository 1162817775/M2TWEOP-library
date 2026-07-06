#pragma once
#include "army.h"
#include "stratModelsChange.h"
#include "graphicsD3D.h"
#include "cultures.h"
#include "faction.h"
#include "gameHelpers.h"
#include "unit.h"

struct aiPersonalityValues;
struct aiLongTermGoalDirector;
struct unitRQ;
struct bannerData;
struct aiRegionData;
struct aiRegionController;
struct settlementStats;
struct settlementStatsManager;
struct aiCampaignController;
struct aiGlobalStrategyDirector;
struct buildingsQueue;
struct buildingInQueue;
struct portBuildingStruct;
struct aiProductionController;
struct regionStruct;
struct aiFaction;
struct buildingLevel;
struct edbEntry;
struct settlementStruct;
struct stringWithHash;
struct unitDb;

struct trackedArmy
{
	DWORD vfTable;
	armyStruct* army;
};

struct generalAssault
{
	DWORD vtbl;
	int8_t finished : 1;
	int8_t started : 1;
	int8_t init : 1;
	int8_t stop : 1;
	character* character;
	int xCoordStart;
	int yCoordStart;
	int xCoordTarget;
	int yCoordTarget;
	settlementStruct* settlement;
	bool nightBattle;
	char pad[3];
};

struct fakeFormSquareVtbl
{
	char pad[0x4C];
	int specPosGetFunc;
	char pad2[0xF4];
};

struct formationGame
{
	fakeFormSquareVtbl* vtbl; 
};

struct formationData
{
	float offsetRowX;
	float offsetRowY;
	float offsetColumnX;
	float offsetColumnY;
	float spacingRows;
	float spacingColumns;
	float angle;
	float entryXRadius;
	float entryYRadius;
	unsigned __int16 entries;
	unsigned __int16 width;
	unsigned __int8 specEntries;
	unsigned __int8 remainder;
	unsigned __int8 training;
	unsigned __int8 allowRandomPerturbations;
	void *auxiliaryData;
	int movingThrough;
};


class patchesForGame
{
public:
	//select worldpkgdesc from db
	static worldRecord* __fastcall selectWorldpkgdesc(char* database, worldRecord* selectedRecord);

	
	static void __fastcall onLoadSettlementWorldpkgdesc(worldRecord* selectedRecord);
	static int __fastcall onFortificationLevelS(settlementStruct* settlement, bool* isCastle);
	static char* __fastcall onSaveEDUStringS(const eduEntry* eduEntry);
	static void __fastcall initGlobalStrategyDirector(aiGlobalStrategyDirector* gsd);
	static int __fastcall onCreateUnit(char** entryName, const int* eduIndex);
	static void __fastcall onSetArmyGeneralsUnit(armyStruct* army);
	static int __fastcall onCalculateMiningIncome(int value, const settlementStruct* settlement);
	static int __fastcall onCreateMercUnitCheck(char** entryName, int eduIndex);
	static void __fastcall onWriteSoldiersToStrat(unit* unit);
	static int __fastcall onSetRegionHiddenResources(int hiddenResourceId, const mapRegion* region);
	static int __fastcall onReadHiddenResources(int hiddenResourceId, void* textBuffer);
	static int __fastcall onGetHiddenResource(const stringWithHash* name);
	static int __fastcall onCheckHiddenResource(int id, int region);
	static int __cdecl onGetWatchTowerRange();
	static void __fastcall posSpecAttackGet(formationGame* form, formationData* data, uint32_t index, vector2* outPos);
	static uint32_t __fastcall onGetNormalPos(const formationData* data, uint32_t index);
	static int __fastcall onGeneralSiegeBug(const generalAssault* assault);
	static void __fastcall onCalculateUnitStats(unitStats* stats, uint32_t wpn, uint32_t armour);
	static void __fastcall onCalculateUnitStatsSoldier(unitStats* stats, const soldierInBattle* soldier);
	static void __fastcall onCalculateUnitStatsOfficer(generalInfo* officer);
	static void __fastcall onInitAutoUnit(autoResolveUnit* autoUnit);
	static void __fastcall onSetSettlementModel(settlementStruct* settlement);
	static int __fastcall onGeneralAssaultAction(generalAssault* assault);
	static int __fastcall onCalcBgSize(character* general, eduEntry* entry);
	static int __fastcall onFixPrec(unitTaskEngage* task);
	static void __fastcall onUpdatePhalanx(unitTaskMeleeAttackPhalanx* task);
	static void __fastcall onInitAttackMelee(soldierInBattle* soldier, actAttackMelee* task);
	static void __fastcall onUpdateBrace(soldierInBattle* soldier);
	static void __fastcall onSpearLocomotion(spearStruct* spear);
	static void __fastcall onAttackSpear(actAttackSpear* action);
	static void __fastcall onUpdateSpear(spearStruct* spear, bool placed, bool complete);
	static void __fastcall onProcessAttackMelee(actionInfo* info, actAttackMelee* task);
	static void __fastcall onInitControllers(aiPersonalityValues* personality);
	static void __fastcall onExitToMenu();
	static void __fastcall onRaiseSpear(spearStruct* spear, bool facingAway, int rank);
	static int __fastcall onCheckOwnership(uint32_t facShifted, const eduEntry* entry);
	static void __fastcall onSpawnArmy(factionStruct* faction, coordPair* coords, armyStruct* army);
	static unit* __fastcall onCreateGeneralUnit(unitDb* edu, character* general, int exp, int wpnlvl, int armlvl, eduEntry* entry); 
	static mountedEngine* __fastcall onGetMountedEngine(const stringWithHash* name);
	static bool __fastcall onParseMountedEngines(mountedEngineDb* db, descrParser* parser);
	static bool __fastcall onParseEdu(unitDb* db, descrParser* parser);
	static int __fastcall onElephantHitpointDamage();
	static int __fastcall onRenderUnitCardNumbers(unit* un);
	static int __fastcall onAddSettlementToDiplomacyScroll(const settlementStruct* settlement);
	static settlementStruct* __fastcall onDecideMissionTarget(settlementStruct* settlement, factionStruct* faction);
	static int __fastcall onCanWithdrawPreBattle(const settlementStruct* settlement);
	static int __cdecl onCalcArrowKillChance(unitStats* stats, soldierInBattle* defender, int16_t angle, int* dir, float heightDiff, int bonus);
	static int __fastcall onCalculateCommand(const characterRecord* general);
	static void __fastcall onRemoveFromUnitQueue(const unitRQ* queue, int index);
	static void __fastcall onLoadModelRigid(model_Rigid* model);
	static void __fastcall onUnloadModels();
	static building* __fastcall onGetBuildingById(const settlementBuildings* buildings, int index);
	static int __fastcall onCheckSettHasBuilding(const settlementBuildings* buildings, int index);
	static void __fastcall getPossibleConstructions(exportDescrBuildings* edb, settlementStruct* sett, void* data, void* caps, void* bonus, bool checkQueue, bool forceTemple);
	static int __fastcall onConflictTest(const buildingsQueue* queue, int index);
	static int __fastcall onOffMapModelThing(int culture);
	static DWORD* __fastcall onSetKhakiText(DWORD* text);
	static int __fastcall onAddBuildingCapsAfterConstruction(const settlementStruct* sett, int index);
	static building* __fastcall onCheckBuildUpgrade(const settlementStruct* sett, int buildingId);
	static void __fastcall onAttachRegionSettlement(settlementStruct* sett, int regionId);
	static int __fastcall onGetTrueBuildingCapabilities(int counter, const stackCapabilities* cap);
	static void __fastcall onCalculateSettlement(settlementStruct* sett);
	static eduEntry* __fastcall onCustomBattleCost(int eduIndexOffset);
	static int __fastcall onMarriageOption(const factionRecord* facRecord);
	static int __fastcall onCalcUnitStatsWpn(int weapon);
	static int __fastcall onCalcUnitValueArmour(int armour);
	static int* __fastcall onGetSupportingArmies(armyStruct* defender, armyStruct* attacker);
	static uint32_t __fastcall onDrawBanner(const trackedArmy* army);
	static bannerData* __fastcall onGetRebelSymbol(const trackedArmy* army, bannerData* oldData);
	static void __fastcall onPredictedStats(settlementStats* statsManager);
	static int __fastcall onEvalAttObjective(const aiCampaignController* controller);
	static void __fastcall onCalculateLTGD(aiLongTermGoalDirector* ltgd);
	static void __fastcall onStartProductionTurn(aiPersonalityValues* personality);
	static factionStruct* __fastcall onCheckGarrison(const aiRegionController* controller);
	static int __fastcall onValidateGarrison(const aiRegionController* controller, const armyStruct* army);
	static void __fastcall onUpdateControllerAlloc(aiCampaignController* controller);
	static int __fastcall onScoreBestCapital(const settlementStruct* sett);
	static int __fastcall onGetUnitCard(const eduEntry* entry, int factionId, stringWithHash* newPath);
	static int __fastcall onGetUnitEduIndex(const stringWithHash* entryName);
	static int __fastcall onGetUnitInfoCard(const eduEntry* entry, int factionId, stringWithHash* newPath);
	static int __fastcall onAssessRequiredStrength(const aiRegionController* controller);
	static int __fastcall onCalcGarrisonStr(const aiRegionData* regData, const factionStruct* fac, const settlementStruct* sett);
	static DWORD* __fastcall onCreateTakeResidenceObjective(aiCampaignController* campaignController, DWORD* oldResidence);
	static void __fastcall onPreBattlePlacement(aiTacticAssault* aiTactic);
	static bool __thiscall onPreBattlePlacement2(aiUnitGroup* group, DWORD formationTemplate, bool forceOrder);
	static eduEntry* __fastcall onCreateMercUnit(char** entryName, eduEntry* entry);
	static eduEntry* __fastcall onCreateUnitWrapper(int eduIndexBase, int removeValue);
	static bool __fastcall onDecideRamAttacks(buildingBattle* gate, aiDetachment* detachment, int numRamsLeft);
	static const char* __fastcall onQuickSave();
	static const char* __fastcall onAutoSave();
	static void balanceMinorSettStats(settlementStats* stats, const settlementStruct* sett);
	static eduEntry* __fastcall onGetRecruitPoolUnitEntry(int eduIndex);
	static int __fastcall onFindUnit(char* entry, int* eduIndex);
	static uint32_t __fastcall onSetExtentsTexture(bool isEnemy);
	static uint8_t __fastcall onSetExtentsBorder(uint8_t isBorder, DWORD extentsDisplay);
	static uint32_t __fastcall onSetExtentsZoc();
	static uint8_t __fastcall onSetExtentsZocAlpha(uint8_t oldAlpha);
	static void __fastcall onDecideNeighbours(factionStruct* faction);
	static void __fastcall onTechtreeSlots(settlementBuildings* buildings, settlementStruct* sett, void* package);
	static void __fastcall onInitGsd(aiGlobalStrategyDirector* director);
	static void __fastcall onInitGsd2(aiGlobalStrategyDirector* director);
	static void __fastcall onSetBuildPolicies(aiProductionController* controller, int policy, int secondaryPolicy);
	static void __fastcall onUpdateProdControllers(aiPersonalityValues* personality);
	static void __fastcall onSetProdPriorities(aiProductionController* controller);
	static DWORD __fastcall onUnitInfo(DWORD entryAddress);
	static void __fastcall onTransferSettlement(const settlementStruct* settlement, int reason, factionStruct* faction);
	static portBuildingStruct* __fastcall onTransferSettlementPort(const settlementStruct* settlement);
	static int __fastcall onCheckConstructionItem(const buildingsQueue* queue, const buildingInQueue* constructionItem);
	static float __fastcall onCalculateUnitValue(eduEntry* entry, DWORD value);
	static int __fastcall onEvaluateUnit(int eduIndex);
	static DWORD __fastcall onCustomBattleUnitCards(DWORD cardArrayThing, int factionID);
	static int __fastcall onCustomBattleUnits(eduEntry** unitArray, int currentCount, int factionID);
	static int __fastcall onAttackGate(unit* unit, void* tactic);
	static eduEntry* __fastcall onEvaluateUnit2(int eduIndex);
	static eduEntry* __fastcall onReadDescrRebel(DWORD value);
	static DWORD __fastcall onSearchUnitType(char* typeName);
	static int __fastcall onReligionCombatBonus(int religionID, characterRecord* namedChar);
	static char* __fastcall getBrowserPicConstructed(int cultureID, edbEntry* entry, int buildingLevel);
	static char* __fastcall getBrowserPicConstruction(int cultureID, edbEntry* entry, int buildingLevel);
	static char* __fastcall getBuildingPic(buildingLevel* level, int cultureID);
	static char* __fastcall getBuildingPicConstructed(buildingLevel* level, int cultureID);
	static char* __fastcall getBuildingPicConstruction(buildingLevel* level, int cultureID);
	static portraitDbEntry* __fastcall getPortraitDbEntry(int cultureID);
	static char* __fastcall onGetGuildOfferPic(DWORD level, int cultureID);
	static unit** __fastcall onGetUnitByLabel(DWORD unitLabels, char* label);
	static unitGroup** __fastcall onGetGroupByLabel(DWORD groupLabels, char* label);
	static char* __fastcall onGetCultureEndTurnSound(int cultureID);
	static void __fastcall onCharacterClicked(character* enemy);
	static DWORD __fastcall onCampaignTick();
	static void __fastcall onBattleTick();


	static character* __fastcall mercenaryMovePointsGetGeneral(armyStruct* army);

	//click at tile
	static void __fastcall clickAtTile(coordPair* xy);

	//after loading of campaign map
	static void WINAPI afterCampaignMapLoaded();

	//after new game start
	static void WINAPI onNewGameStart();
	//after reading EDU
	static void WINAPI onEduParsed();
	static void WINAPI onGameInit();
	static void WINAPI onUnloadCampaign();
	static void WINAPI onNewGameLoaded();
	static void __fastcall onAiTurn(aiFaction* aiFac);
	
	//before start of a first faction turn
	static void WINAPI onChangeTurnNum();

	//on console command give_trait, after searching for character
	static void WINAPI onGiveTrait();

	//after loading campaign or battle data
	static void WINAPI afterLoadGameData();

	//after comparison in I_CompareCounter command
	static void WINAPI afterI_CompareCounter();

	//check fort for deleting
	static int WINAPI checkFort();

	//add suzerain dip state
	static int WINAPI checkDipString();
	static int WINAPI checkFacDip();

	//spawn_army command patch
	static int WINAPI spawnArmyCoords();
	static void WINAPI spawnEndArmyCoords();

	//spawn_character command patch
	static int WINAPI spawnCharacterCoords();

	//check and replace characters battle models before battle
	static void WINAPI onBattleStratScreen();


	//parse events in this functions
	static void __fastcall onEvent(DWORD** vTab, DWORD arg2);

	//load game
	static void __fastcall onLoadSaveFile(UNICODE_STRING**& savePath);
	//save game
	static void __fastcall onSaveGame(UNICODE_STRING**& savePath);

	//check of custom tile before battle, replace it here
	static void __fastcall onTileCheck(int* coords);
	//read custom tiles file and make right strings, structures, etc
	static void WINAPI readTilesFile();


	//read and load all startmap models
	static void WINAPI unicalStratModsRead();
	static void WINAPI loadCharStratModels();
	//moment before game start select stratmap models for drawing
	//replace models for the settlements, forts, ports, etc here without craches
	static void WINAPI checkAndChangeModels();
	
	static void WINAPI battleLoaded();
	static void WINAPI toReadGameDbsAtStart();
	
	static void WINAPI onDrawPartsOfStratObjects();
	static void WINAPI onDrawAll();
	static void WINAPI onStartOfDrawFunction();
	static void WINAPI onRetreat();


	static void __fastcall onStopCharacter(character* character);
	static void WINAPI onMoveRecruitQueue();
	static eduEntry* __fastcall recruitEopUnit(int eduIndex);
	static void __fastcall recruitEopUnit2(int eduIndex);
	static void __fastcall recruitEopMercUnit(DWORD pad, DWORD pad2, regionStruct* region, int eduIndex, int factionID, int exp);


	static void __fastcall onEndSiege(settlementStruct* sett);
	static void __fastcall onStartSiege(settlementStruct* sett);
	static void __fastcall onLoadDescrBattleCharacter(armyStruct* army, character* goalGen);


	//called not in all cases!
	static void WINAPI onBattleStateChange();

	static void __thiscall onFactionSymbolSelect();
	static void __thiscall onCharacterDied(character* character);
	static void __thiscall onFactionDied(factionStruct* faction);
	static void __thiscall onCharacterSwitchFaction(character* character);
};

class consolePatches
{
public:
	static void WINAPI onGameConsoleCommandFromConsole();
	static void WINAPI onGameConsoleCommandFromScript();

	static int __fastcall onReadLogonOrLogoff(int isLogonNow);
};


struct color8888
{
	uint8_t b;
	uint8_t g;
	uint8_t r;
	uint8_t a;
	uint32_t asInt() const
	{
		return (a << 24) | (r << 16) | (g << 8) | b;
	}
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////// MIN HOOK FUNCTIONS //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

class minHookFunctions
{
public:
	static void init();
	static MH_STATUS hook(LPVOID pTarget, LPVOID pDetour, LPVOID* ppOriginal, std::string function);
	static void draw();


	static bool openConsole;
	static oneTile* selectTile;
	static coordPair rememberCoords;

  
	using t_onUnitCreate = unit*(__thiscall*)(unitDb* _this, regionStruct* region, stringWithHash* id, int factionID, int combat_ability, int soldiers, int armour_lvl, int weapon_lvl);
	static t_onUnitCreate o_onUnitCreate;
	static unit* __thiscall onUnitCreate(unitDb* _this, regionStruct* region, stringWithHash* id, int factionID, int combat_ability, int soldiers, int armour_lvl, int weapon_lvl);
	static bool isUnlockWeaponLimit;
	
	using t_debugRenderLine = void(__cdecl*)(vector2* start, vector2* end, color8888 color, float time, bool zbuffered, float hOffset);
	static t_debugRenderLine o_debugRenderLine;
	static void __cdecl debugRenderLine(vector2* start, vector2* end, color8888 color, float time, bool zbuffered, float hOffset = 0.f);
	
	using t_debugRenderPeg = void(__cdecl*)(vector2* start, float height, color8888 color, float time);
	static t_debugRenderPeg o_debugRenderPeg;
	static void __cdecl debugRenderPeg(vector2* start, float height, color8888 color, float time);
	
	using t_displayMissileStats = int(__thiscall*)(eduEntry* entry, int exp, int wpn);
	static t_displayMissileStats o_displayMissileStats;
	static int __thiscall displayMissileStats(eduEntry* entry, int exp, int wpn);
	
	using t_displayMeleeStats = int(__thiscall*)(eduEntry* entry, int exp, int wpn);
	static t_displayMeleeStats o_displayMeleeStats;
	static int __thiscall displayMeleeStats(eduEntry* entry, int exp, int wpn);
	
	using t_displayArmourStats = int(__thiscall*)(eduEntry* entry, int armourUpg);
	static t_displayArmourStats o_displayArmourStats;
	static int __thiscall displayArmourStats(eduEntry* entry, int armourUpg);
	
	using t_displayDefenseStats = int(__thiscall*)(eduEntry* entry, int exp, int armourUpg);
	static t_displayDefenseStats o_displayDefenseStats;
	static int __thiscall displayDefenseStats(eduEntry* entry, int exp, int armourUpg);
	
	using t_fleeConstructor = void*(__thiscall*)(void* flee, void* sett, void* ch, bool action, bool back, bool clearMp);
	static t_fleeConstructor o_fleeConstructor1;
	static t_fleeConstructor o_fleeConstructor2;
	static void* __thiscall fleeConstructor1(void* flee, void* sett, void* ch, bool action, bool back, bool clearMp);
	static void* __thiscall fleeConstructor2(void* flee, void* sett, void* ch, bool action, bool back, bool clearMp);
	
	using t_debugRenderCircle = void(__cdecl*)(vector2* center, float radius, int segments, color8888 color, float time);
	static t_debugRenderCircle o_debugRenderCircle;
	static void __cdecl debugRenderCircle(vector2* center, float radius, int segments, color8888 color, float time);
	
	using t_debugLineAdd = void(__thiscall*)(vector2* start, vector2* end, color8888 color, float time, bool zbuffered, float hOffset);
	static t_debugLineAdd o_debugLineAdd;
	static int __thiscall debugLineAdd(void*, vector3* start, vector3* end, color8888 color, float time, bool zbuffered);

	using t_onMaybeWillSpyOpenGates = bool(__thiscall*)(void* _this, character* general);
	static t_onMaybeWillSpyOpenGates o_onMaybeWillSpyOpenGates;
	static bool __thiscall onMaybeWillSpyOpenGates(void* _this, character* general);

	using t_onCharacterSwitchFaction = void(__thiscall*)(character* _this, factionStruct* faction, int param_2, int param_3);
	static t_onCharacterSwitchFaction o_onCharacterSwitchFaction;
	static void __thiscall onCharacterSwitchFaction(character* _this, factionStruct* faction, int param_2, int param_3);

	using t_onPlayGameSound = void(__cdecl*)(DWORD _this, int sound);
	static t_onPlayGameSound o_onPlayGameSound;
	static void __cdecl onPlayGameSound(DWORD _this, int sound);
	static DWORD lastSoundClass;

	using t_onCreateWife = characterRecord*(__thiscall*)(characterRecord* husband);
	static t_onCreateWife o_onCreateWife;
	static characterRecord* __thiscall onCreateWife(characterRecord* husband);

	using t_onCreateMessageAboutMarriage = void(__cdecl*)(characterRecord* husband, characterRecord* new_wife, marriageOption* mo);
	static t_onCreateMessageAboutMarriage o_onCreateMessageAboutMarriage;
	static void __cdecl onCreateMessageAboutMarriage(characterRecord* husband, characterRecord* new_wife, marriageOption* mo);
	static characterRecord* createWife(characterRecord* husband);

	using t_onCreateCandidateMarrying = characterRecord*(__thiscall*)(characterRecord* husband);
	static t_onCreateCandidateMarrying o_onCreateCandidateMarrying;
	static characterRecord* __thiscall onCreateCandidateMarrying(characterRecord* daughter);

	using t_onDaughterReadyMarryHusband = void(__cdecl*)(characterRecord* daughter, characterRecord* new_husband, marriageOption* mo);
	static t_onDaughterReadyMarryHusband o_onDaughterReadyMarryHusband;
	static void __cdecl onDaughterReadyMarryHusband(characterRecord* daughter, characterRecord* new_husband, marriageOption* mo);
	static characterRecord* createHusband(characterRecord* husband);
};

#define GET_VARIABLE_NAME(Variable) (#Variable)
#define MIN_HOOK(pTarget, pDetour, ppOriginal) minHookFunctions::hook((LPVOID)pTarget, (LPVOID)pDetour, reinterpret_cast<void**>(&ppOriginal), GET_VARIABLE_NAME(pDetour))

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////







