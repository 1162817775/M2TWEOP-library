![EOP Logo](https://i.imgur.com/jqzoYoQ.png)

[![ko-fi](https://ko-fi.com/img/githubbutton_sm.svg)](https://ko-fi.com/D1D4DZTHG)
[![Discord Link](https://img.shields.io/discord/713369537948549191?color=red&label=Discord&style=for-the-badge)](https://discord.gg/Epqjm8u2WK)
[![Build Status](https://img.shields.io/github/v/release/youneuoy/M2TWEOP-library?label=Download&style=for-the-badge)](#download)

## **Release Notes**

It has been over 2 years since EOP V3.3.1 released. In that time, the entire project has been re-written and restructed from scratch by Fynn. We thank him for this massive contribution to this release along with all the other people who have reported many bugs, assisted in reversing efforts and/or contributed financially to support the project. There are a wealth of features not documented here as so much work was done, it was hard to remember exactly what has been achieved!

### **Project Structure**
- The general structure of the project has changed.
  - OLD: `youneuoyData/plugins/lua/luaPluginScript.lua`
  - NEW: `eopData/eopScripts/luaPluginScript.lua`
- Everything is self-contained within the `eopData` folder so in order to migrate from V3 to V4 you just need to move the files in the correct place - *Fynn*
- Redistributables (C++ and DirectX) were removed and are instead downloadable if necessary - *Fynn*

### **Lua Plugin**
- HUNDREDS of new Lua functions have been added! Please see the [Lua API Release Notes: New Functions & Tables](#lua-api-release-notes-new-functions--tables) below for all the new functions and tables added in V4. - *Fynn*
- Stopped the game still receiving keyboard/mouse inputs when the EOP Console was open - *Medik*
- Added a "Clear Input" toggle in the console - *Medik*
- Added `Copy to clipboard` button for console output - *Medik*
- Added `Open Documentation` button in the console - *Medik*
- A toast popup appears when `reloadLua()` and `restartLua()` is called to provide feedback that the restart/reload was successful - *Medik*
- Updated Lua exception message box error handling - *Medik*
  - Abort (Exits the game completely)
  - Retry (Runs `restartLua()` in the background, very useful when stuck in `draw()` error loops)
  - Ignore (Ignore the error and just continue)
  - Use the `showLuaRetryIgnore` option to enable this behaviour

### **Launcher**
- Added [Freecam](https://www.moddb.com/mods/freecam-medieval-2) integration - *Medik*
  - Enable the integration to automatically launch and close Freecam whenever you play the game
- Updated [DXVK](https://github.com/doitsujin/dxvk/releases/tag/v2.5) to v2.5 - *Medik*
- Allow users to specify a mod version which is displayed in the top left beneath the EOP version at launch - *Medik*
- Allow users to specify a website and discord link which can be clicked in the launcher - *Medik*
- Launcher no longer continues to play music if Discord Rich Presence is enabled and background music is enabled - *Medik*
- Renamed "M2TWEOP GUI.exe" to "M2TWEOP_GUI.exe" - *Medik*
- Allow users to disable the "backup saves" feature so they don't get spammed with multiple saves - *Medik*

### **Library**
- Automatically convert non-EOP saves to EOP saves - *Fynn*
- Reduced amount of EOP "branding" displayed on startup - *Medik*
- Now multiple hero abilities in generated battles works - *youneuoy*
- Added support for starting/closing an OpenTelemetry Collector service - *Medik*

### **ImGUI**
- Updated default scrollbar theming - *Medik*
- Fixed a bug where `reloadLua()` and `restartLua()` no longer require opening the console - *Medik*

### **Documentation**
- Updated Erken's ImGUI PDF tutorial to V5 (Thanks Erken!) - *Medik*

### **Examples**
What mods have been made using EOP V4 so far?
  - [Divide and Conquer: AGO V3](https://www.divide-and-conquer-ago.com/features/#battle-ai)

### **Links**
- [Known Bugs](https://github.com/youneuoy/M2TWEOP-library/issues/71)
- [Website](https://youneuoy.github.io/M2TWEOP-library/)
- [FAQ](https://youneuoy.github.io/M2TWEOP-library/faq.html)
- [Lua Documentation](https://youneuoy.github.io/M2TWEOP-library/_static/LuaLib/index.html)
- [ImGUI Documentation](https://youneuoy.github.io/M2TWEOP-library/_static/LuaLib/extra/readme_imgui.md.html)
- [Discord](https://discord.gg/Epqjm8u2WK)
- [Installation Video](https://youtu.be/caOiB0NaGGI?t=67)
- [M2TWEOP Tutorials](https://www.youtube.com/playlist?list=PLi6V3nVH22N7ZfjfOuivGKHnNRAlBaTQd)
- [M2TWEOP Features](https://www.youtube.com/playlist?list=PLi6V3nVH22N6R7IGupVDwfyiPm6-d6rlU)

### **Download**

<a id="download"></a>


# Lua API Release Notes: New Functions & Tables

## Table of Contents
1. [New Top-Level Tables / Namespaces](#1-new-top-level-tables--namespaces)
2. [Renamed / Restructured Classes](#2-renamed--restructured-classes)
3. [New M2TWEOP Functions](#3-new-m2tweop-functions)
4. [New M2TWEOPDU Functions](#4-new-m2tweopdu-functions)
5. [New EDB Functions](#5-new-edb-functions)
6. [New 3D Objects System (M2TWEOP3dObjects / eop3dText)](#6-new-3d-objects-system)
7. [New armyStruct Functions (replaces stackStruct)](#7-new-armystruct-functions)
8. [New character Functions](#8-new-character-functions)
9. [New characterRecord Functions (replaces namedCharacter)](#9-new-characterrecord-table--functions)
10. [New factionStruct Functions](#10-new-factionstruct-functions)
11. [New factionRecord Table & Functions](#11-new-factionrecord-table--functions)
12. [New campaignStruct Functions](#12-new-campaignstruct-functions)
13. [New settlementStruct Functions](#13-new-settlementstruct-functions)
14. [New fortStruct Functions](#14-new-fortstruct-functions)
15. [New buildingLevel Table & Functions](#15-new-buildinglevel-table--functions)
16. [New EOP AI System (eopAiConfig / aiFactionData)](#16-new-eop-ai-system)
17. [New Character Movement System](#17-new-character-movement-system)
18. [New Rebel Faction System](#18-new-rebel-faction-system)
19. [New Diplomacy Table (factionDiplomacy)](#19-new-diplomacy-table)
20. [New Battle-Related Tables & Functions](#20-new-battle-related-tables--functions)
21. [New stratMap Functions](#21-new-stratmap-functions)
22. [New Region / Neighbour Functions](#22-new-region--neighbour-functions)
23. [New EDU Entry Functions](#23-new-edu-entry-functions)
24. [New AI Functions](#24-new-ai-functions)
25. [New UI Functions & Tables](#25-new-ui-functions--tables)
26. [New Miscellaneous Tables](#26-new-miscellaneous-tables)
27. [New Ancillary / Trait Functions](#27-new-ancillary--trait-functions)
28. [New Event Callbacks](#28-new-event-callbacks)
29. [New Functions on Other Existing Types](#29-new-functions-on-other-existing-types)

---

## 1. New Top-Level Tables / Namespaces

### `M2TW` (replaces `gameDataAll`)
Central access point for major game systems:
- `M2TW.battle` — battleStruct
- `M2TW.campaign` — campaignStruct
- `M2TW.uiCardManager` — uiCardManager
- `M2TW.stratMap` — stratMap
- `M2TW.selectionInfo` — selectionInfo

### `M2TWEOP3dObjects`
New namespace for 3D text rendering in the game world.

### `eopAiConfig`
New namespace for the EOP AI configuration system.

---

## 2. Renamed / Restructured Classes

| Old Name                | New Name                                  |
| ----------------------- | ----------------------------------------- |
| `stackStruct`           | `armyStruct`                              |
| `namedCharacter`        | `characterRecord`                         |
| `gameDataAll`           | `M2TW`                                    |
| `stratmap.objects.*`    | Moved to `M2TWEOP.*` or `stratMap.*`      |
| `stratmap.camera.*`     | Moved to `stratMap.*`                     |
| `stratmap.game.*`       | Moved to `M2TWEOP.*` / `campaignStruct.*` |
| `recruitpool`           | `recruitPool` (capitalization fix)        |
| `factionStratMapStruct` | Removed (fields integrated elsewhere)     |
| `fireRate`              | Removed                                   |
| `terrainHills`          | Merged into `terrainFeatures`             |
| `terrainLines`          | Merged into `terrainFeatures`             |
| `battleStreets`         | Removed                                   |
| `roadNode`              | Removed                                   |

---

## 3. New M2TWEOP Functions

```lua
M2TWEOP.getModFolderName()
M2TWEOP.getAncillary(name)
M2TWEOP.getAncillaryByIndex(index)
M2TWEOP.getAncillaryCount()
M2TWEOP.getTrait(name)
M2TWEOP.getTraitByIndex(index)
M2TWEOP.getTraitCount()
M2TWEOP.copyFile(from, to)
M2TWEOP.setExpandedString(key, value)
M2TWEOP.getExpandedString(key)
M2TWEOP.setStratString(key, value)
M2TWEOP.getStratString(key)
M2TWEOP.setMinBgSize(newSize)
M2TWEOP.setExtraLeaderSoldiers(newSize)
M2TWEOP.setExtraHeirSoldiers(newSize)
M2TWEOP.setTextureCacheSize()
M2TWEOP.unlockWeaponLimit()
M2TWEOP.getStratHoveredCoords()
M2TWEOP.getBattleHoveredCoords()
M2TWEOP.getTileMoveCost(originX, originY, targetX, targetY)
M2TWEOP.addModelToGame(path, modelId, isSettlement)
M2TWEOP.setModel(xCoord, yCoord, modelId, modelId2)
M2TWEOP.callConsole(command, args)
M2TWEOP.setScriptCounter(counterName, value)
M2TWEOP.getScriptCounter(counterName)
M2TWEOP.scriptCommand(command, args)
M2TWEOP.getEopAiConfig()
M2TWEOP.getRebelFaction(name)
M2TWEOP.getFactionRecord(factionID)
M2TWEOP.getFactionRecordNum()
M2TWEOP.hideUnknownUnitTooltips(set)
M2TWEOP.useEopFrontiers(set)
M2TWEOP.ignoreOwnershipRecruitment(set)
M2TWEOP.changeGeneralPosition(set)
M2TWEOP.modelExists(modelName)
M2TWEOP.setApIsShieldPiercing(set)
M2TWEOP.handleUnitCards(set)
M2TWEOP.setWeaponBonusModifier(modifier)
M2TWEOP.setArmourUpgradeModifier(modifier)
M2TWEOP.setPhalanxMissileDefense(bonus)
M2TWEOP.setSchiltromMissileDefense(bonus)
M2TWEOP.setShieldWallMissileDefense(bonus)
M2TWEOP.setElephantHitpointDamage(damage)
M2TWEOP.setElephantJavBonus(bonus)
M2TWEOP.enableRangedWeaponUpg(set)
M2TWEOP.drawUnitCardOutline(set)
M2TWEOP.setWatchTowerRange(newRange)
M2TWEOP.enableFamilyEventsWithoutTree(set)
M2TWEOP.setKhakiTextColor(r, g, b)
M2TWEOP.getMinorSettlementBalance()
M2TWEOP.generateSprite(modelName)
M2TWEOP.getGroundTypeMoveCost(groundType)
M2TWEOP.setGroundTypeMoveCost(groundType, moveCost)
M2TWEOP.addBanner(name, filePath, topLeftX, topLeftY, bottomRightX, bottomRightY)
```

---

## 4. New M2TWEOPDU Functions

```lua
M2TWEOPDU.getEduEntryNum()
M2TWEOPDU.getEopEntryNum()
M2TWEOPDU.findGeneralUnit(factionID)
M2TWEOPDU.findGeneralUpgradeUnit(factionID)
```

> **Note:** Several old functions had typo fixes (`eopEnryIndex` → `eopEntryIndex`, `EnryIndex` → `EntryIndex`). Many old granular stat getter/setter functions on `M2TWEOPDU` (e.g. `getEntryStat`, `setEntryStat`, `getEntryAttackAttribute`, `setEntryAttackAttribute`, `setEntryInfoCardTga`, `setEntryLocalizedName`, etc.) have been replaced by direct field access on the `eduEntry` class.

---

## 5. New EDB Functions

```lua
EDB.getBuildingByID(index)
EDB.getBuildingNum()
EDB.getGuild(index)
EDB.getGuildByName(name)
EDB.getGuildNum()
```

> **Note:** Old static `EDB.setBuildingPic*`, `EDB.setBuildingLocalized*`, `EDB.addBuildingCapability`, `EDB.addBuildingPool`, `EDB.getBuildingCapability*`, `EDB.getBuildingPool*`, `EDB.removeBuildingCapability`, `EDB.removeBuildingPool`, `EDB.getEopBuildEntry` have been replaced by methods on the new `buildingLevel` class and `edbEntry:getBuildingLevel()`.

---

## 6. New 3D Objects System

### `M2TWEOP3dObjects` functions
```lua
M2TWEOP3dObjects.makeTextFont(fontName, weight, isItalic)
M2TWEOP3dObjects.deleteTextFont(fondID)
M2TWEOP3dObjects.make3dText(fondID, text)
```

### `eop3dText` class (new)
Fields: `xSize`, `ySize`, `zSize`, `xRoll`, `yRoll`, `zRoll`, `xCoord`, `yCoord`, `zCoord`

```lua
eop3dText:scale(sizeMultiplier)
eop3dText:changeColor(a, r, g, b)
eop3dText:setCoords(x, y, z)
eop3dText:startDrawing()
eop3dText:stopDrawing()
eop3dText:drawOnce()
eop3dText:delete()
```

---

## 7. New armyStruct Functions

Beyond the functions carried over from `stackStruct`, these are new:

```lua
armyStruct:liftSiege()
armyStruct:liftBlockade()
armyStruct:canStartSiege(target)
armyStruct:canStartSiegeFort(target)
armyStruct:canStartAssault(target)
armyStruct:canStartAssaultFort(target)
armyStruct:isEnemyTo(other)
armyStruct:isAllyTo(other)
armyStruct:isEnemyToFaction(fac)
armyStruct:isAllyToFaction(fac)
armyStruct:moveTactical(x, y, forceMerge)
armyStruct:getNumberOfCategory(category)
```

> **Note:** `createUnit` and `createUnitByIDX` now accept an additional `soldiers` parameter. The old `stackStruct:createEOPUnit` has been removed.

---

## 8. New character Functions

```lua
character:isGeneral()
character:hasFreeTilesToMove()
character:joinCrusade()
character:joinJihad()
character:leaveCrusade(triggerEvent)
character:leaveJihad(triggerEvent)
character:getMovementExtents(searchType, turns)
character:createMoveData(searchType, turns)
```

---

## 9. New characterRecord Table & Functions

The `characterRecord` class replaces `namedCharacter` with significantly expanded fields including all the old fields plus many new stat fields (`ambush`, `artilleryCommand`, `assassination`, `attack`, `battleSurgery`, `bodyguardSize`, `bodyguardValour`, `boldness`, `bribeResistance`, `bribery`, `cavalryCommand`, `charm`, `construction`, `defence`, `disposition`, `electability`, `eligibility`, `farming`, `fertility`, `finance`, `footInTheDoor`, etc.) and family tree fields (`parent`, `spouse`, `children`).

### New functions (beyond those from namedCharacter)
```lua
characterRecord:isLeader()
characterRecord:isHeir()
characterRecord:getTrait(index)
characterRecord:getTraitLevel(traitName)
characterRecord:addTraitPoints(traitName, points)
characterRecord:acquireAncillary(ancillaryName, noDuplicate)
characterRecord:hasAncillary(ancName)
characterRecord:hasAncType(ancType)
characterRecord:setPortrait(portraitPath)
characterRecord:giveRandomPortrait(cultureID, religionID)
characterRecord:giveRandomName(nameFactionId)
characterRecord:giveValidLabel()
characterRecord:getEopSetModel()
characterRecord:birthChild(name, lastName, age, isMale, isAlive)
characterRecord:marryWife(name, age)
```

---

## 10. New factionStruct Functions

```lua
factionStruct:getArmy(number)                    -- replaces getStack
factionStruct:getCharacterRecord(number)         -- replaces getNamedCharacter
factionStruct:getCharacterByLabel(label)
factionStruct:getSpottedCharacter(number)
factionStruct:getCharacterCountOfType(charType)
factionStruct:getMapInfo(fromFaction)
factionStruct:createCharacter(type, age, name, name2, subFaction, portrait_custom, xCoord, yCoord)
factionStruct:spawnArmy(name, name2, type, label, portrait, x, y, age, family, subFaction, unitIndex, exp, wpn, armour, soldiers)
factionStruct:addSettlement(xCoord, yCoord, name, level, castle)
factionStruct:setLeader(newLeader, onlyLeader)
factionStruct:setCapital(newCapital)
factionStruct:setColor(R, G, B)
factionStruct:setSecondaryColor(R, G, B)
factionStruct:setFactionBanner(facName)
factionStruct:canSeeCharacter(candidate)
factionStruct:ancillaryExists(ancName)
factionStruct:getTileVisibility(x, y)
factionStruct:setTileVisibility(x, y, visibility)
factionStruct:revealTile(x, y)
factionStruct:hideRevealedTile(x, y)
factionStruct:isNeighbourRegion(regionID)
factionStruct:createFortXY(X, Y, cultureID)      -- now takes cultureID param
```

---

## 11. New factionRecord Table & Functions

Entirely new class with extensive fields for faction definition data:

Fields include: `primaryColorRed/Green/Blue`, `secondaryColorRed/Green/Blue`, `triumphValue`, `religionID`, `name`, `standardIndex`, `logoIndex`, `smallLogoIndex`, `customBattleAvailability`, `periodsUnavailableInCustomBattle`, `canSap`, `prefersNavalInvasions`, `canHavePrincess`, `canHorde`, `hasFamilyTree`, `teutonic`, `disbandToPools`, `canBuildSiegeTowers`, `canTransmitPlague`, `shadowedByID`, `shadowingID`, `spawnsOnRevoltID`, `spawnsOnRevoltOwnerID`, `spawnsOnEvent`, `roman`, `barbarian`, `eastern`, `slave`, `hordeMinUnits`, `hordeMaxUnits`, `reductionPerHorde`, `hordeUnitPerSettlementPop`, `hordeMinNamedCharacters`, `hordeMaxPercentArmyStack`, `cultureID`

```lua
factionRecord:setFactionStratModel(model, characterType, level)
factionRecord:setFactionBattleModel(model, characterType)
factionRecord:getLocalizedName()
```

---

## 12. New campaignStruct Functions

```lua
campaignStruct:getFactionByID(factionID)
campaignStruct:getFactionByOrder(index)
campaignStruct:getFactionDiplomacy(factionIDOne, factionIDTwo)
campaignStruct:getPlayerFaction(index)
campaignStruct:isPlayableFaction(factionID)
campaignStruct:isPlayerFaction(factionID)
campaignStruct:isExistingFaction(factionID)
campaignStruct:getNumberOfMarriages(factionIDOne, factionIDTwo)
campaignStruct:getMercPool(index)                  -- now takes integer index
campaignStruct:getMercPoolByName(name)
campaignStruct:getSettlement(index)
campaignStruct:getCharacterByLabel(label)
campaignStruct:worldwideAncillaryExists(ancName)
campaignStruct:getRoad(index)
campaignStruct:getCampaignPath()
campaignStruct.addCharacterCas(skeleton, caspath, shadowcaspath, typename, texturepath, scale)
campaignStruct.historicEvent(eventName, title, body, isChoice, xCoord, yCoord, factions)
campaignStruct.execScriptEvent(name, eventType, xCoord, yCoord, scale, movie)
campaignStruct.getUnitSize()
```

---

## 13. New settlementStruct Functions

```lua
settlementStruct:buildingPresent(buildingName)
settlementStruct:buildingPresentMinLevel(buildingLevelName, exact)
settlementStruct:canConstructBuilding(entry, level)
settlementStruct:createArmyInSettlement()
settlementStruct:getCharacter(index)
settlementStruct:getFortificationLevel()
settlementStruct:getUnitInQueue(index)
settlementStruct:createBuilding(buildingLevelName)   -- now takes building level name string
```

---

## 14. New fortStruct Functions

```lua
fortStruct:changeOwner(newFaction, convertGarrison)  -- renamed from changeFortOwner
fortStruct:getCharacter(index)
fortStruct:isAllyToFaction(otherFac)
fortStruct:isEnemyToFaction(otherFac)
```

---

## 15. New buildingLevel Table & Functions

Entirely new class for per-level building manipulation (replaces old `EDB` static functions):

Fields: `name`, `genericBuildingPic`, `genericBuildingPicConstructed`, `genericBuildingPicConstruction`, `buildCost`, `buildTime`, `capabilityNum`, `recruitPoolNum`, `factionCapabilityNum`, `settlementMinLvl`, `availableCastle`, `availableCity`

```lua
edbEntry:getBuildingLevel(index)

buildingLevel:setBuildingPic(cultureID, path)
buildingLevel:getBuildingPic(cultureID)
buildingLevel:setBuildingPicConstructed(cultureID, path)
buildingLevel:getBuildingPicConstructed(cultureID)
buildingLevel:setBuildingPicConstruction(cultureID, path)
buildingLevel:getBuildingPicConstruction(cultureID, path)
buildingLevel:setLocalizedName(factionID, name)
buildingLevel:getLocalizedName(factionID)
buildingLevel:setLocalizedDescr(factionID, descr)
buildingLevel:getLocalizedDescr(factionID)
buildingLevel:setLocalizedDescrShort(factionID, descr)
buildingLevel:getLocalizedDescrShort(factionID)
buildingLevel:getCapability(index)
buildingLevel:getFactionCapability(index)
buildingLevel:getRecruitPool(index)
buildingLevel:addCapability(capability, value, bonus, condition)
buildingLevel:addFactionCapability(capability, value, bonus, condition)
buildingLevel:addRecruitPool(eduIndex, initialSize, gainPerTurn, maxSize, exp, condition)
buildingLevel:removeCapability(index)
buildingLevel:removeFactionCapability(index)
buildingLevel:removeRecruitPool(index)
```

---

## 16. New EOP AI System

### `eopAiConfig` class (new)
Fields: `enabled`, `enableLogging`, `aggressionFactor`, `defenseFactor`, `residenceFactor`, `aidFactor`, `moveCostFactor`, `powerFactor`, `nonBorderFactor`, `invadePriorityFactor`, `maxTurnSearchCount`

```lua
eopAiConfig.getFactionData(fac)
```

### `aiFactionData` class (new)
```lua
aiFactionData:setTargetFactionFactor(fac, factor)
aiFactionData:setAidFactionFactor(fac, factor)
aiFactionData:setSettlementFactor(sett, factor)
aiFactionData:setTargetReligionFactor(religionID, factor)
aiFactionData:setAidReligionFactor(religionID, factor)
```

---

## 17. New Character Movement System

### `characterMovementExtents` class (new)
Fields: `searchType`, `totalTiles`, `xCoordMin`, `yCoordMin`, `xCoordMax`, `yCoordMax`, `turns`, `character`

```lua
characterMovementExtents:getTile(xCoord, yCoord)
```

### `movementExtentTile` class (new)
Fields: `tile`, `moveCost`, `turns`

### `characterMoveData` class (new)
Fields: `character`, `xCoord`, `yCoord`, `searchType`, `turns`, `settlementCount`, `fortCount`, `tileCount`, `armyCount`, `resourceCount`, `characterCount`, `moveExtents`

```lua
characterMoveData:getSettlement(index)
characterMoveData:getCharacter(index)
characterMoveData:getArmy(index)
characterMoveData:getResource(index)
characterMoveData:getFort(index)
characterMoveData:getTile(index)
characterMoveData:sortSettlementsDistance()
characterMoveData:sortSettlementsStrength()
characterMoveData:sortArmiesDistance()
characterMoveData:sortArmiesStrength()
characterMoveData:sortFortsDistance()
characterMoveData:sortFortsStrength()
```

### `moveDataSettlement` class (new)
Fields: `settlement`, `moveCost`, `turns`, `ownFaction`

### `moveDataCharacter` class (new)
Fields: `character`, `moveCost`, `turns`, `ownFaction`

### `moveDataArmy` class (new)
Fields: `army`, `moveCost`, `turns`, `ownFaction`

### `moveDataResource` class (new)
Fields: `resource`, `moveCost`, `turns`, `ownFaction`

### `moveDataFort` class (new)
Fields: `fort`, `moveCost`, `turns`, `ownFaction`

### `moveDataTile` class (new)
Fields: `tile`, `moveCost`, `turns`, `xCoord`, `yCoord`

### `stratMovePath` class (new)
Fields: `totalCost`

```lua
stratMovePath:getPathCoords(index)
```

---

## 18. New Rebel Faction System

### `eopRebelFaction` class (new)
Fields: `name`, `rebelEntry`, `bannerRed`, `bannerGreen`, `bannerBlue`, `bannerSet`

```lua
eopRebelFaction:setBannerSymbol(bannerName)
eopRebelFaction:addCharacterModel(modelName)
```

### `rebelFaction` class (new)
Fields: `index`, `name`, `category`, `chance`, `totalUnitCount`

```lua
rebelFaction:getCategory(index)
```

### `rebelCategory` class (new)
Fields: `unitCount`

```lua
rebelCategory:getUnit(index)
```

### `rebelUnit` class (new)
Fields: `unitName`, `category`, `soldierCount`, `armour`, `weapon`

---

## 19. New Diplomacy Table

### `factionDiplomacy` class (new)
Fields: `previousState`, `state`, `hasTradeRights`, `hasMilitaryAccess`, `isTrustWorthy`, `isProtectorate`, `isKnown`, `lastDiplomaticResult`, `factionStanding`, `protectoratePayment`, `numTurnsAllied`, `numTurnsWar`, `numTurnsState`, `numTurnsTrade`, `numTurnsAccess`, `numTurnsProtectorate`, `numTreaties`, `numAssists`, `numAssistFailures`, `numEmptyThreats`, `numValidThreats`, `leaveTerritoryTimer`, `winsInBattle`, `tributeAmount`, `tributeDuration`, `turnsSinceLastMeeting`, `diplomaticSuccess`, `diplomaticBalance`, `lastMapInfoTrade`, `numTurnsCeasefire`

---

## 20. New Battle-Related Tables & Functions

### `battleStruct` new functions
```lua
battleStruct:getPlayerArmy(index)
battleStruct.getBattleResidence()
battleStruct.getUnitByLabel(label)
battleStruct.getGroupByLabel(label)
battleStruct.getBattleMapHeight(xCoord, yCoord)
battleStruct.getBattlefieldEngines()
battleStruct.getBattleTile(xCoord, yCoord)
battleStruct.getZoneID(xCoord, yCoord)
battleStruct.getPosPerimeter(xCoord, yCoord)
battleStruct.isZoneValid(zoneID)
battleStruct:isRiverBattle()
```

### `battleSide` new functions
```lua
battleSide.getWinConditionString(condition)
battleSide:getBattleArmy(index)
battleSide:getFaction(index)
battleSide:getReinforcementArmy(index)
battleSide:hasFaction(factionID)
```

### `battleSideArmy` new function
```lua
battleSideArmy:getDeployArea(index)
```

### `deploymentAreaS` new function
```lua
deploymentAreaS:getCoordPair(index)
```

### `battleAI` new functions
```lua
battleAI:getObjective(index)
battleAI:getVisibleEnemy(index)
battleAI:getUnit(index)
```

### `battleObjective` new functions
```lua
battleObjective:getUnit(index)
battleObjective:getType()
```

### `battleArmy` new function
```lua
battleArmy:getBattleUnit(index)
```

### `battleResidence` new function
```lua
battleResidence:getStreetPosition(index)
```

### `battleBuildings` new functions
```lua
battleBuildings:getBuilding(index)
battleBuildings:getPerimeter(index)
```

### `perimeterBuildings` new function
```lua
perimeterBuildings:getBuilding(index)
```

### `plazaData` new function
```lua
plazaData:getSoldierCount(alliance)
```

### `terrainFeatures` new functions
```lua
terrainFeatures:getLine(index)
terrainFeatures:getHill(index)
```

### `battleBuildingStats` new function
```lua
battleBuildingStats:getTowerStats(index)
```

### New battle classes
- **`siegeEquipmentQueueItem`** — siege equipment queue item data
- **`battleStrengthStruct`** — battle strength data
- **`lineData`** — battle AI line data
- **`streetPosition`** — battle street position data
- **`generalBattleStruct`** — general in battle data (fields: `unit`, `record`, `stats`, `isGeneral`, `isAlive`)

### `siegeStruct` new function
```lua
siegeStruct:getQueueItem(index)
```

---

## 21. New stratMap Functions

```lua
stratMap.moveCamera(xCoord, yCoord)
stratMap.jumpCamera(xCoord, yCoord)
stratMap.zoomCamera(distance)
stratMap.startDrawModelAt(modelId, x, y, sizeMultiplier)
stratMap.stopDrawModel(modelId)
stratMap.replaceTile(label, xCoord, yCoord, filename, weather, dayTime)
stratMap.findValidTileNearTile(x, y, characterType)
stratMap.getMovePath(fromX, fromY, destX, destY)
stratMap.rebuildFrontiers()
stratMap.setEnemyExtentsColor(r, g, b, a, border)
stratMap.setOwnExtentsColor(r, g, b, a, border)
stratMap.setZocColor(r, g, b, a)
stratMap:isInBounds(x, y)
```

---

## 22. New Region / Neighbour Functions

```lua
regionStruct:getArmy(index)
regionStruct:getSettlement(index)
regionStruct:getLandingPoint(index)
regionStruct:getEnemySettsToFaction(factionID)
regionStruct:getNeutralSettsToFaction(factionID)
regionStruct:getResourcesValue()
regionStruct:hasFaction(factionID)
regionStruct:getHiddenResource(name)               -- now takes string name
regionStruct:setHiddenResource(name, enable)        -- now takes string name
```

### `neighbourRegion` new functions
```lua
neighbourRegion:getBorderTile(index)
neighbourRegion:getFrontierTile(index)
neighbourRegion:getAmbushTile(index)
neighbourRegion:getDeepFrontierTile(index)
neighbourRegion:getBorderCrossing(index)
```

### New classes
- **`landingPoint`** — fields: `landTile`, `moveCost`, `seaTile`
- **`landingTile`** — fields: `tile`, `moveCost`

---

## 23. New EDU Entry Functions

```lua
eduEntry:setOwnership(factionID, setOwnership)      -- renamed from setOwnerShip
eduEntry:getArmourLevel(index)
eduEntry:getArmourLevelNum()
eduEntry:getArmourModel(index)
eduEntry:getArmourModelNum()
eduEntry:setArmourLevel(index, level)
eduEntry:setArmourModel(index, model)
```

### New EDU-related classes
- **`attackStats`** — full weapon/attack stat breakdown (fields: `isValid`, `isMissile`, `isSpear`, `isLightSpear`, `isPrec`, `isAP`, `isBP`, `isArea`, `isFire`, `isBodyLaunching`, `isThrown`, `isShortPike`, `isLongPike`, `isSpearBonus12/10/8/6/4`, `attack`, `charge`, `ammo`, `range`, `rangeSquared`, `projectile`, `weaponType`, `techType`, `damageType`, `soundType`, `minAttackDelayPri`, `weaponFX`)
- **`defenseStats`** — fields: `isValid`, `armour`, `defense`, `shield`, `armourMaterial`
- **`unitStats`** — fields: `attackStats`, `defenseStats`, `attackInBattle`, `armourInBattle`, `formationDefBonus`, `formationAttBonus`, `generalsBonus`, `chargeBonus`, `chargeDecay`

---

## 24. New AI Functions

### `aiLongTermGoalDirector` new functions
```lua
aiLongTermGoalDirector:getLongTermGoalValues(targetFactionID)  -- renamed from getlongTermGoalValues
aiLongTermGoalDirector:isTrustedAlly(targetFactionID)
aiLongTermGoalDirector:isTrustedAllyEnemy(targetFaction)
aiLongTermGoalDirector:regionsBordersOnlyTrusted(regionID)
aiLongTermGoalDirector:getInvasionTargetNum(regionID)
aiLongTermGoalDirector:getInvasionTargetPriority(regionID)
aiLongTermGoalDirector:reset()
```

### `aiPersonality` new functions
```lua
aiPersonality:getAgentValue(type)
aiPersonality:setAgentValue(type, value)
aiPersonality:getConstructionAgentValue(type)
aiPersonality:setConstructionAgentValue(type, value)
aiPersonality:getConstructionUnitValue(type)
aiPersonality:setConstructionUnitValue(type, value)
```

### `aiProductionController` new functions
```lua
aiProductionController:getExtraBias(type)
aiProductionController:setExtraBias(type, value)
```

---

## 25. New UI Functions & Tables

### `uiFamilyTree` class (new)
Fields: `familyRoot`, `generations`, `hoveredLeaf`, `selectedLeaf`, `canSelectAll`

### `uiFamilyLeaf` class (new)
Fields: `record`, `generation`, `parent`, `spouse`, `numChildren`

```lua
uiFamilyLeaf:getChild(index)
```

### `uiCardManager` new functions
```lua
uiCardManager.getBuildingInfoScroll()    -- changed from instance method to static
uiCardManager.getUnitInfoScroll()        -- changed from instance method to static
uiCardManager.getFamilyTree()            -- new
```

### `mapImageStruct` new function
```lua
mapImageStruct:exportImage(name)
```

### `options2` new functions
```lua
options2:isHotseatPlayer(factionID)
options2:setHotseatPlayer(factionID, set)
```

---

## 26. New Miscellaneous Tables

### `weatherData` class (new)
Fields: `fogMin`, `fogMax`, `windStrength`, `rainType`, `rainLevel`

### `minorSettlementBalance` class (new)
Fields: `incomeModifierBase`, `growthModifierBase`, `incomeModifierAllianceOffset`, `growthModifierAllianceOffset`, `incomeModifierNeutralOffset`, `growthModifierNeutralOffset`, `incomeModifierTradeRightsOffset`, `growthModifierTradeRightsOffset`, `incomeModifierOwnFaction`, `growthModifierOwnFaction`

### `vector3` class (new)
Fields: `xCoord`, `yCoord`, `zCoord`

### `cardinal` class (new)
Individual cardinal data for the College of Cardinals.

### `crusadeReward` class (new)
Fields: `money`, `experience`

### `missionDetailsStruct` class (new)
Fields: `missionName`, `paybackName`

### `unitAiGroupData` class (new)
Fields: `group`, `battleObjective`, `inMelee`, `isAvailable`

### `mercPool` new functions
```lua
mercPool:getMercUnitNum()
mercPool:addMercUnit(idx, exp, cost, repmin, repmax, maxunits, startpool, startyear, endyear, crusading)
mercPool:getMercUnit(idx)
```

### `mercPoolUnit` new function
```lua
mercPoolUnit:setMercReligion(religion, set)
```

### `collegeOfCardinals` new functions
```lua
collegeOfCardinals:getCardinal(index)
collegeOfCardinals:getElectionResult(index)
```

### `crusadeStruct` new functions
```lua
crusadeStruct:start(target, timeToJoin, caller)
crusadeStruct:stop(result)
crusadeStruct:factionJoined(factionID)
crusadeStruct:factionJoinedLastTurn(factionID)
crusadeStruct:factionFought(factionID)
crusadeStruct:factionInTarget(factionID)
crusadeStruct:getReward(factionID)
```

### `jihadStruct` new functions
```lua
jihadStruct:start(target, timeToJoin, caller)
jihadStruct:stop(result)
jihadStruct:factionJoined(factionID)
jihadStruct:factionJoinedLastTurn(factionID)
jihadStruct:factionFought(factionID)
jihadStruct:factionInTarget(factionID)
jihadStruct:getReward(factionID)
```

### `tradeResource` new function
```lua
tradeResource:hasMineBuilt()
```

---

## 27. New Ancillary / Trait Functions

### `ancillary` new functions
```lua
ancillary:getEffect(index)
ancillary:isCultureExcluded(cultureId)
```

### `traitEntry` new functions
```lua
traitEntry:getLevel(index)
traitEntry:isCharacterTypeValid(characterType)
traitEntry:isCultureExcluded(cultureId)
```

---

## 28. New Event Callbacks

```lua
onBattleTick()
onCampaignTick()
onCalculateLTGD(ltgd)
onSetProductionControllers(personality)
onSpawnArmy(army)
onCharacterClicked(clickedCharacter)
onEduParsed()
onExitToMenu()
onNewGameLoaded()
onFactionSymbolSelect(factionID)
onFortificationLevelS(siegedSettlement)    -- renamed from onfortificationlevelS
onRemoveFromUnitQueue(item)
```

---

## 29. New Functions on Other Existing Types

### `unit` new functions
```lua
unit:hasAttribute(attributeName)          -- now takes attributeName parameter
unit:useSpecialAbility(heroOnly)          -- now takes heroOnly parameter
unit:getActionStatusInt()
unit:isFiring()
unit:isIdle()
```

### `unitPositionData` new function
```lua
unitPositionData:getActionType()
```

### `mountStruct` new function
```lua
mountStruct:getElephantRiderOffset(index)
```
