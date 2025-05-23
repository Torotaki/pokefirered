@ commands
	.macro attackcanceler
	.byte 0x0
	.endm

	.macro accuracycheck param0:req, param1:req
	.byte 0x1
	.4byte \param0
	.2byte \param1
	.endm

	.macro attackstring
	.byte 0x2
	.endm

	.macro ppreduce
	.byte 0x3
	.endm

	.macro critcalc
	.byte 0x4
	.endm

	.macro damagecalc
	.byte 0x5
	.endm

	.macro typecalc
	.byte 0x6
	.endm

	.macro adjustnormaldamage
	.byte 0x7
	.endm

	.macro adjustnormaldamage2
	.byte 0x8
	.endm

	.macro attackanimation
	.byte 0x9
	.endm

	.macro waitanimation
	.byte 0xa
	.endm

	.macro healthbarupdate battler:req
	.byte 0xb
	.byte \battler
	.endm

	.macro datahpupdate battler:req
	.byte 0xc
	.byte \battler
	.endm

	.macro critmessage
	.byte 0xd
	.endm

	.macro effectivenesssound
	.byte 0xe
	.endm

	.macro resultmessage
	.byte 0xf
	.endm

	.macro printstring id:req
	.byte 0x10
	.2byte \id
	.endm

	.macro printselectionstring id:req
	.byte 0x11
	.2byte \id
	.endm

	.macro waitmessage param0:req
	.byte 0x12
	.2byte \param0
	.endm

	.macro printfromtable ptr:req
	.byte 0x13
	.4byte \ptr
	.endm

	.macro printselectionstringfromtable ptr:req
	.byte 0x14
	.4byte \ptr
	.endm

	.macro seteffectwithchance
	.byte 0x15
	.endm

	.macro seteffectprimary
	.byte 0x16
	.endm

	.macro seteffectsecondary
	.byte 0x17
	.endm

	.macro clearstatusfromeffect battler:req
	.byte 0x18
	.byte \battler
	.endm

	.macro tryfaintmon battler:req
	.byte 0x19
	.byte \battler
	.byte FALSE
	.4byte NULL
	.endm

	.macro tryfaintmon_spikes battler:req, ptr:req
	.byte 0x19
	.byte \battler
	.byte TRUE
	.4byte \ptr
	.endm

	.macro dofaintanimation battler:req
	.byte 0x1a
	.byte \battler
	.endm

	.macro cleareffectsonfaint battler:req
	.byte 0x1b
	.byte \battler
	.endm

	.macro jumpifstatus battler:req, status1:req, ptr:req
	.byte 0x1c
	.byte \battler
	.4byte \status1
	.4byte \ptr
	.endm

	.macro jumpifstatus2 battler:req, status2:req, ptr:req
	.byte 0x1d
	.byte \battler
	.4byte \status2
	.4byte \ptr
	.endm

	.macro jumpifability param0:req, ability:req, ptr:req
	.byte 0x1e
	.byte \param0
	.byte \ability
	.4byte \ptr
	.endm

	.macro jumpifsideaffecting battler:req, sidestatus:req, ptr:req
	.byte 0x1f
	.byte \battler
	.2byte \sidestatus
	.4byte \ptr
	.endm

	.macro jumpifstat battler:req, ifflag:req, stat:req, value:req, ptr
	.byte 0x20
	.byte \battler
	.byte \ifflag
	.byte \stat
	.byte \value
	.4byte \ptr
	.endm

	.macro jumpifstatus3condition battler:req, status3:req, param2:req, ptr:req
	.byte 0x21
	.byte \battler
	.4byte \status3
	.byte \param2
	.4byte \ptr
	.endm

	.macro jumpiftype battler:req, type:req, ptr:req
	.byte 0x22
	.byte \battler
	.byte \type
	.4byte \ptr
	.endm

	.macro getexp battler:req
	.byte 0x23
	.byte \battler
	.endm

	.macro checkteamslost ptr:req
	.byte 0x24
	.4byte \ptr
	.endm

	.macro movevaluescleanup
	.byte 0x25
	.endm

	.macro setmultihit value:req
	.byte 0x26
	.byte \value
	.endm

	.macro decrementmultihit value:req
	.byte 0x27
	.4byte \value
	.endm

	.macro goto ptr:req
	.byte 0x28
	.4byte \ptr
	.endm

	.macro jumpifbyte ifflag:req, param1:req, param2:req, param3:req
	.byte 0x29
	.byte \ifflag
	.4byte \param1
	.byte \param2
	.4byte \param3
	.endm

	.macro jumpifhalfword ifflag:req, param1:req, param2:req, param3:req
	.byte 0x2a
	.byte \ifflag
	.4byte \param1
	.2byte \param2
	.4byte \param3
	.endm

	.macro jumpifword ifflag:req, param1:req, param2:req, param3:req
	.byte 0x2b
	.byte \ifflag
	.4byte \param1
	.4byte \param2
	.4byte \param3
	.endm

	.macro jumpifarrayequal param0:req, param1:req, param2:req, param3:req
	.byte 0x2c
	.4byte \param0
	.4byte \param1
	.byte \param2
	.4byte \param3
	.endm

	.macro jumpifarraynotequal param0:req, param1:req, param2:req, param3:req
	.byte 0x2d
	.4byte \param0
	.4byte \param1
	.byte \param2
	.4byte \param3
	.endm

	.macro setbyte ptr:req, param1:req
	.byte 0x2e
	.4byte \ptr
	.byte \param1
	.endm

	.macro addbyte ptr:req, param1:req
	.byte 0x2f
	.4byte \ptr
	.byte \param1
	.endm

	.macro subbyte ptr:req, param1:req
	.byte 0x30
	.4byte \ptr
	.byte \param1
	.endm

	.macro copyarray param0:req, param1:req, param2:req
	.byte 0x31
	.4byte \param0
	.4byte \param1
	.byte \param2
	.endm

	.macro copyarraywithindex param0:req, param1:req, param2:req, param3:req
	.byte 0x32
	.4byte \param0
	.4byte \param1
	.4byte \param2
	.byte \param3
	.endm

	.macro orbyte ptr:req, param1:req
	.byte 0x33
	.4byte \ptr
	.byte \param1
	.endm

	.macro orhalfword ptr:req, param1:req
	.byte 0x34
	.4byte \ptr
	.2byte \param1
	.endm

	.macro orword ptr:req, param1:req
	.byte 0x35
	.4byte \ptr
	.4byte \param1
	.endm

	.macro bicbyte ptr:req, param1:req
	.byte 0x36
	.4byte \ptr
	.byte \param1
	.endm

	.macro bichalfword ptr:req, param1:req
	.byte 0x37
	.4byte \ptr
	.2byte \param1
	.endm

	.macro bicword ptr:req, param1:req
	.byte 0x38
	.4byte \ptr
	.4byte \param1
	.endm

	.macro pause param0:req
	.byte 0x39
	.2byte \param0
	.endm

	.macro waitstate
	.byte 0x3a
	.endm

	.macro healthbar_update battler:req
	.byte 0x3b
	.byte \battler
	.endm

	.macro return
	.byte 0x3c
	.endm

	.macro end
	.byte 0x3d
	.endm

	.macro end2
	.byte 0x3e
	.endm

	.macro end3
	.byte 0x3f
	.endm

	.macro jumpifaffectedbyprotect ptr:req
	.byte 0x40
	.4byte \ptr
	.endm

	.macro call ptr:req
	.byte 0x41
	.4byte \ptr
	.endm

	.macro jumpiftype2 battler:req, type:req, ptr:req
	.byte 0x42
	.byte \battler
	.byte \type
	.4byte \ptr
	.endm

	.macro jumpifabilitypresent ability:req, ptr:req
	.byte 0x43
	.byte \ability
	.4byte \ptr
	.endm

	.macro endselectionscript
	.byte 0x44
	.endm

	.macro playanimation battler:req, animType:req, arg=NULL
	.byte 0x45
	.byte \battler
	.byte \animType
	.4byte \arg
	.endm

	.macro playanimation_var battler:req, animType:req, arg=NULL
	.byte 0x46
	.byte \battler
	.4byte \animType
	.4byte \arg
	.endm

	.macro setgraphicalstatchangevalues
	.byte 0x47
	.endm

	.macro playstatchangeanimation battler:req, param1:req, param2:req
	.byte 0x48
	.byte \battler
	.byte \param1
	.byte \param2
	.endm

	.macro moveend param0:req, param1:req
	.byte 0x49
	.byte \param0
	.byte \param1
	.endm

	@ Help macros for 5 uses of moveend command

	@ All cases
	.macro moveendall
	setbyte sMOVEEND_STATE, 0
	moveend 0, 0
	.endm

	@ Chosen case
	.macro moveendcase case:req
	setbyte sMOVEEND_STATE, \case
	moveend 1, 0
	.endm

	@ All cases from (inclusive)
	.macro moveendfrom from:req
	setbyte sMOVEEND_STATE, \from
	moveend 0, 0
	.endm

	@ All cases from 0 to (not inclusive)
	.macro moveendto to:req
	setbyte sMOVEEND_STATE, 0
	moveend 2, \to
	.endm

	@ Cases from (inclusive) to (not inclusive)
	.macro moveendfromto from:req, to:req
	setbyte sMOVEEND_STATE, \from
	moveend 2, \to
	.endm

	.macro typecalc2
	.byte 0x4a
	.endm

	.macro returnatktoball
	.byte 0x4b
	.endm

	.macro getswitchedmondata battler:req
	.byte 0x4c
	.byte \battler
	.endm

	.macro switchindataupdate battler:req
	.byte 0x4d
	.byte \battler
	.endm

	.macro switchinanim battler:req, dontclearsubstitutebit:req
	.byte 0x4e
	.byte \battler
	.byte \dontclearsubstitutebit
	.endm

	.macro jumpifcantswitch battler:req, ptr:req
	.byte 0x4f
	.byte \battler
	.4byte \ptr
	.endm

	.macro openpartyscreen param0:req, param1:req
	.byte 0x50
	.byte \param0
	.4byte \param1
	.endm

	.macro switchhandleorder battler:req, param1:req
	.byte 0x51
	.byte \battler
	.byte \param1
	.endm

	.macro switchineffects battler:req
	.byte 0x52
	.byte \battler
	.endm

	.macro trainerslidein battler:req
	.byte 0x53
	.byte \battler
	.endm

	.macro playse song:req
	.byte 0x54
	.2byte \song
	.endm

	.macro fanfare song:req
	.byte 0x55
	.2byte \song
	.endm

	.macro playfaintcry battler:req
	.byte 0x56
	.byte \battler
	.endm

	.macro endlinkbattle
	.byte 0x57
	.endm

	.macro returntoball battler:req
	.byte 0x58
	.byte \battler
	.endm

	.macro handlelearnnewmove param0:req, param1:req, param2:req
	.byte 0x59
	.4byte \param0
	.4byte \param1
	.byte \param2
	.endm

	.macro yesnoboxlearnmove param0:req
	.byte 0x5a
	.4byte \param0
	.endm

	.macro yesnoboxstoplearningmove param0:req
	.byte 0x5b
	.4byte \param0
	.endm

	.macro hitanimation battler:req
	.byte 0x5c
	.byte \battler
	.endm

	.macro getmoneyreward addr
	.byte 0x5d
	.4byte \addr
	.endm

	.macro updatebattlermoves battler:req
	.byte 0x5e
	.byte \battler
	.endm

	.macro swapattackerwithtarget
	.byte 0x5f
	.endm

	.macro incrementgamestat param0:req
	.byte 0x60
	.byte \param0
	.endm

	.macro drawpartystatussummary battler:req
	.byte 0x61
	.byte \battler
	.endm

	.macro hidepartystatussummary battler:req
	.byte 0x62
	.byte \battler
	.endm

	.macro jumptocalledmove param0:req
	.byte 0x63
	.byte \param0
	.endm

	.macro statusanimation battler:req
	.byte 0x64
	.byte \battler
	.endm

	.macro status2animation battler:req, status2:req
	.byte 0x65
	.byte \battler
	.4byte \status2
	.endm

	.macro chosenstatusanimation battler:req, param1:req, param2:req
	.byte 0x66
	.byte \battler
	.byte \param1
	.4byte \param2
	.endm

	.macro yesnobox
	.byte 0x67
	.endm

	.macro cancelallactions
	.byte 0x68
	.endm

	.macro adjustsetdamage
	.byte 0x69
	.endm

	.macro removeitem battler:req
	.byte 0x6a
	.byte \battler
	.endm

	.macro atknameinbuff1
	.byte 0x6b
	.endm

	.macro drawlvlupbox
	.byte 0x6c
	.endm

	.macro resetsentmonsvalue
	.byte 0x6d
	.endm

	.macro setatktoplayer0
	.byte 0x6e
	.endm

	.macro makevisible battler:req
	.byte 0x6f
	.byte \battler
	.endm

	.macro recordlastability battler:req
	.byte 0x70
	.byte \battler
	.endm

	.macro buffermovetolearn
	.byte 0x71
	.endm

	.macro jumpifplayerran ptr:req
	.byte 0x72
	.4byte \ptr
	.endm

	.macro hpthresholds battler:req
	.byte 0x73
	.byte \battler
	.endm

	.macro hpthresholds2 battler:req
	.byte 0x74
	.byte \battler
	.endm

	.macro useitemonopponent
	.byte 0x75
	.endm

	.macro various battler:req, param1:req
	.byte 0x76
	.byte \battler
	.byte \param1
	.endm

	.macro setprotectlike
	.byte 0x77
	.endm

	.macro tryexplosion
	.byte 0x78
	.endm

	.macro setatkhptozero
	.byte 0x79
	.endm

	.macro jumpifnexttargetvalid ptr:req
	.byte 0x7a
	.4byte \ptr
	.endm

	.macro tryhealhalfhealth param0:req, battler:req
	.byte 0x7b
	.4byte \param0
	.byte \battler
	.endm

	.macro trymirrormove
	.byte 0x7c
	.endm

	.macro setrain
	.byte 0x7d
	.endm

	.macro setreflect
	.byte 0x7e
	.endm

	.macro setseeded
	.byte 0x7f
	.endm

	.macro manipulatedamage param0:req
	.byte 0x80
	.byte \param0
	.endm

	.macro trysetrest param0:req
	.byte 0x81
	.4byte \param0
	.endm

	.macro jumpifnotfirstturn ptr:req
	.byte 0x82
	.4byte \ptr
	.endm

	.macro nop
	.byte 0x83
	.endm

	.macro jumpifcantmakeasleep param0:req
	.byte 0x84
	.4byte \param0
	.endm

	.macro stockpile
	.byte 0x85
	.endm

	.macro stockpiletobasedamage param0:req
	.byte 0x86
	.4byte \param0
	.endm

	.macro stockpiletohpheal param0:req
	.byte 0x87
	.4byte \param0
	.endm

	.macro negativedamage
	.byte 0x88
	.endm

	.macro statbuffchange param0:req, param1:req
	.byte 0x89
	.byte \param0
	.4byte \param1
	.endm

	.macro normalisebuffs
	.byte 0x8a
	.endm

	.macro setbide
	.byte 0x8b
	.endm

	.macro confuseifrepeatingattackends
	.byte 0x8c
	.endm

	.macro setmultihitcounter param0:req
	.byte 0x8d
	.byte \param0
	.endm

	.macro initmultihitstring
	.byte 0x8e
	.endm

	.macro forcerandomswitch param0:req
	.byte 0x8f
	.4byte \param0
	.endm

	.macro tryconversiontypechange param0:req
	.byte 0x90
	.4byte \param0
	.endm

	.macro givepaydaymoney
	.byte 0x91
	.endm

	.macro setlightscreen
	.byte 0x92
	.endm

	.macro tryKO param0:req
	.byte 0x93
	.4byte \param0
	.endm

	.macro damagetohalftargethp
	.byte 0x94
	.endm

	.macro setsandstorm
	.byte 0x95
	.endm

	.macro weatherdamage
	.byte 0x96
	.endm

	.macro tryinfatuating param0:req
	.byte 0x97
	.4byte \param0
	.endm

	.macro updatestatusicon battler:req
	.byte 0x98
	.byte \battler
	.endm

	.macro setmist
	.byte 0x99
	.endm

	.macro setfocusenergy
	.byte 0x9a
	.endm

	.macro transformdataexecution
	.byte 0x9b
	.endm

	.macro setsubstitute
	.byte 0x9c
	.endm

	.macro mimicattackcopy param0:req
	.byte 0x9d
	.4byte \param0
	.endm

	.macro metronome
	.byte 0x9e
	.endm

	.macro dmgtolevel
	.byte 0x9f
	.endm

	.macro psywavedamageeffect
	.byte 0xa0
	.endm

	.macro counterdamagecalculator param0:req
	.byte 0xa1
	.4byte \param0
	.endm

	.macro mirrorcoatdamagecalculator param0:req
	.byte 0xa2
	.4byte \param0
	.endm

	.macro disablelastusedattack param0:req
	.byte 0xa3
	.4byte \param0
	.endm

	.macro trysetencore param0:req
	.byte 0xa4
	.4byte \param0
	.endm

	.macro painsplitdmgcalc param0:req
	.byte 0xa5
	.4byte \param0
	.endm

	.macro settypetorandomresistance param0:req
	.byte 0xa6
	.4byte \param0
	.endm

	.macro setalwayshitflag
	.byte 0xa7
	.endm

	.macro copymovepermanently param0:req
	.byte 0xa8
	.4byte \param0
	.endm

	.macro trychoosesleeptalkmove param0:req
	.byte 0xa9
	.4byte \param0
	.endm

	.macro setdestinybond
	.byte 0xaa
	.endm

	.macro trysetdestinybondtohappen
	.byte 0xab
	.endm

	.macro remaininghptopower
	.byte 0xac
	.endm

	.macro tryspiteppreduce param0:req
	.byte 0xad
	.4byte \param0
	.endm

	.macro healpartystatus
	.byte 0xae
	.endm

	.macro cursetarget param0:req
	.byte 0xaf
	.4byte \param0
	.endm

	.macro trysetspikes param0:req
	.byte 0xb0
	.4byte \param0
	.endm

	.macro setforesight
	.byte 0xb1
	.endm

	.macro trysetperishsong param0:req
	.byte 0xb2
	.4byte \param0
	.endm

	.macro rolloutdamagecalculation
	.byte 0xb3
	.endm

	.macro jumpifconfusedandstatmaxed stat:req, ptr:req
	.byte 0xb4
	.byte \stat
	.4byte \ptr
	.endm

	.macro furycuttercalc
	.byte 0xb5
	.endm

	.macro friendshiptodamagecalculation
	.byte 0xb6
	.endm

	.macro presentdamagecalculation
	.byte 0xb7
	.endm

	.macro setsafeguard
	.byte 0xb8
	.endm

	.macro magnitudedamagecalculation
	.byte 0xb9
	.endm

	.macro jumpifnopursuitswitchdmg param0:req
	.byte 0xba
	.4byte \param0
	.endm

	.macro setsunny
	.byte 0xbb
	.endm

	.macro maxattackhalvehp param0:req
	.byte 0xbc
	.4byte \param0
	.endm

	.macro copyfoestats param0:req
	.byte 0xbd
	.4byte \param0
	.endm

	.macro rapidspinfree
	.byte 0xbe
	.endm

	.macro setdefensecurlbit
	.byte 0xbf
	.endm

	.macro recoverbasedonsunlight param0:req
	.byte 0xc0
	.4byte \param0
	.endm

	.macro hiddenpowercalc
	.byte 0xc1
	.endm

	.macro selectfirstvalidtarget
	.byte 0xc2
	.endm

	.macro trysetfutureattack param0:req
	.byte 0xc3
	.4byte \param0
	.endm

	.macro trydobeatup param0:req, param1:req
	.byte 0xc4
	.4byte \param0
	.4byte \param1
	.endm

	.macro setsemiinvulnerablebit
	.byte 0xc5
	.endm

	.macro clearsemiinvulnerablebit
	.byte 0xc6
	.endm

	.macro setminimize
	.byte 0xc7
	.endm

	.macro sethail
	.byte 0xc8
	.endm

	.macro trymemento ptr:req
	.byte 0xc9
	.4byte \ptr
	.endm

	.macro setforcedtarget
	.byte 0xca
	.endm

	.macro setcharge
	.byte 0xcb
	.endm

	.macro callterrainattack
	.byte 0xcc
	.endm

	.macro cureifburnedparalysedorpoisoned param0:req
	.byte 0xcd
	.4byte \param0
	.endm

	.macro settorment param0:req
	.byte 0xce
	.4byte \param0
	.endm

	.macro jumpifnodamage param0:req
	.byte 0xcf
	.4byte \param0
	.endm

	.macro settaunt param0:req
	.byte 0xd0
	.4byte \param0
	.endm

	.macro trysethelpinghand param0:req
	.byte 0xd1
	.4byte \param0
	.endm

	.macro tryswapitems param0:req
	.byte 0xd2
	.4byte \param0
	.endm

	.macro trycopyability param0:req
	.byte 0xd3
	.4byte \param0
	.endm

	.macro trywish param0:req, param1:req
	.byte 0xd4
	.byte \param0
	.4byte \param1
	.endm

	.macro trysetroots param0:req
	.byte 0xd5
	.4byte \param0
	.endm

	.macro doubledamagedealtifdamaged
	.byte 0xd6
	.endm

	.macro setyawn param0:req
	.byte 0xd7
	.4byte \param0
	.endm

	.macro setdamagetohealthdifference param0:req
	.byte 0xd8
	.4byte \param0
	.endm

	.macro scaledamagebyhealthratio
	.byte 0xd9
	.endm

	.macro tryswapabilities param0:req
	.byte 0xda
	.4byte \param0
	.endm

	.macro tryimprison param0:req
	.byte 0xdb
	.4byte \param0
	.endm

	.macro trysetgrudge param0:req
	.byte 0xdc
	.4byte \param0
	.endm

	.macro weightdamagecalculation
	.byte 0xdd
	.endm

	.macro assistattackselect param0:req
	.byte 0xde
	.4byte \param0
	.endm

	.macro trysetmagiccoat param0:req
	.byte 0xdf
	.4byte \param0
	.endm

	.macro trysetsnatch param0:req
	.byte 0xe0
	.4byte \param0
	.endm

	.macro trygetintimidatetarget param0:req
	.byte 0xe1
	.4byte \param0
	.endm

	.macro switchoutabilities battler:req
	.byte 0xe2
	.byte \battler
	.endm

	.macro jumpifhasnohp battler:req, param1:req
	.byte 0xe3
	.byte \battler
	.4byte \param1
	.endm

	.macro getsecretpowereffect
	.byte 0xe4
	.endm

	.macro pickup
	.byte 0xe5
	.endm

	.macro docastformchangeanimation
	.byte 0xe6
	.endm

	.macro trycastformdatachange
	.byte 0xe7
	.endm

	.macro settypebasedhalvers param0:req
	.byte 0xe8
	.4byte \param0
	.endm

	.macro setweatherballtype
	.byte 0xe9
	.endm

	.macro tryrecycleitem param0:req
	.byte 0xea
	.4byte \param0
	.endm

	.macro settypetoterrain param0:req
	.byte 0xeb
	.4byte \param0
	.endm

	.macro pursuitrelated param0:req
	.byte 0xec
	.4byte \param0
	.endm

	.macro snatchsetbattlers
	.byte 0xed
	.endm

	.macro removelightscreenreflect
	.byte 0xee
	.endm

	.macro handleballthrow
	.byte 0xef
	.endm

	.macro givecaughtmon
	.byte 0xf0
	.endm

	.macro trysetcaughtmondexflags param0:req
	.byte 0xf1
	.4byte \param0
	.endm

	.macro displaydexinfo
	.byte 0xf2
	.endm

	.macro trygivecaughtmonnick param0:req
	.byte 0xf3
	.4byte \param0
	.endm

	.macro subattackerhpbydmg
	.byte 0xf4
	.endm

	.macro removeattackerstatus1
	.byte 0xf5
	.endm

	.macro finishaction
	.byte 0xf6
	.endm

	.macro finishturn
	.byte 0xf7
	.endm

	.macro fixedhealing param0:req, battler:req
	.byte 0xf8
	.4byte \param0
	.byte \battler
	.endm

@ various command changed to more readable macros
	.macro cancelmultiturnmoves battler:req
	various \battler, VARIOUS_CANCEL_MULTI_TURN_MOVES
	.endm

	.macro setmagiccoattarget battler:req
	various \battler, VARIOUS_SET_MAGIC_COAT_TARGET
	.endm

	.macro getifcantrunfrombattle battler:req
	various \battler, VARIOUS_IS_RUNNING_IMPOSSIBLE
	.endm

	.macro getmovetarget battler:req
	various \battler, VARIOUS_GET_MOVE_TARGET
	.endm

	.macro getbattlerfainted battler:req
	various \battler, VARIOUS_GET_BATTLER_FAINTED
	.endm

	.macro resetintimidatetracebits battler:req
	various \battler, VARIOUS_RESET_INTIMIDATE_TRACE_BITS
	.endm

	.macro updatechoicemoveonlvlup battler:req
	various \battler, VARIOUS_UPDATE_CHOICE_MOVE_ON_LVL_UP
	.endm

	.macro resetplayerfainted
	various BS_ATTACKER, VARIOUS_RESET_PLAYER_FAINTED
	.endm

	.macro getbattlersforrecall
	various BS_ATTACKER, VARIOUS_GET_BATTLERS_FOR_RECALL
	.endm

	.macro returnopponentmon1toball
	various BS_ATTACKER, VARIOUS_RETURN_OPPONENT_MON1
	.endm

	.macro returnopponentmon2toball
	various BS_ATTACKER, VARIOUS_RETURN_OPPONENT_MON2
	.endm

	.macro checkpokeflute battler:req
	various \battler, VARIOUS_CHECK_POKEFLUTE
	.endm

	.macro waitfanfare battler:req
	various \battler, VARIOUS_WAIT_FANFARE
	.endm

@ helpful macros
	.macro setstatchanger stat:req, stages:req, down:req
	setbyte sSTATCHANGER \stat | \stages << 4 | \down << 7
	.endm

	.macro setmoveeffect effect:req
	setbyte cEFFECT_CHOOSER, \effect
	.endm

	.macro chosenstatus1animation battler:req, status:req
	chosenstatusanimation \battler, 0x0, \status
	.endm

	.macro chosenstatus2animation battler:req, status:req
	chosenstatusanimation \battler, 0x1, \status
	.endm

	.macro sethword dst:req, value:req
	setbyte \dst, (\value) & 0xFF
	setbyte \dst + 1, ((\value) >> 8) & 0xFF
	.endm

	.macro setword dst:req, value:req
	setbyte \dst, (\value) & 0xFF
	setbyte \dst + 1, ((\value) >> 8) & 0xFF
	setbyte \dst + 2, ((\value) >> 16) & 0xFF
	setbyte \dst + 3, ((\value) >> 24) & 0xFF
	.endm

	.macro copybyte dst:req, src:req
	copyarray \dst, \src, 0x1
	.endm

	.macro copyhword dst:req, src:req
	copyarray \dst, \src, 0x2
	.endm

	.macro copyword dst:req, src:req
	copyarray \dst, \src, 0x4
	.endm

	.macro jumpifbytenotequal byte1:req, byte2:req, jumpptr:req
	jumpifarraynotequal \byte1, \byte2, 0x1, \jumpptr
	.endm

	.macro jumpifbyteequal byte1:req, byte2:req, jumpptr:req
	jumpifarrayequal \byte1, \byte2, 0x1, \jumpptr
	.endm

	.macro jumpifmove move:req, jumpptr:req
	jumpifhalfword CMP_EQUAL, gCurrentMove, \move, \jumpptr
	.endm

	.macro jumpifnotmove move:req, jumpptr:req
	jumpifhalfword CMP_NOT_EQUAL, gCurrentMove, \move, \jumpptr
	.endm

	.macro jumpifstatus3 battler:req, status:req, jumpptr:req
	jumpifstatus3condition \battler, \status, 0x0, \jumpptr
	.endm

	.macro jumpifnostatus3 battler:req, status:req, jumpptr:req
	jumpifstatus3condition \battler, \status, 0x1, \jumpptr
	.endm

	.macro jumpifmovehadnoeffect jumpptr:req
	jumpifbyte CMP_COMMON_BITS, gMoveResultFlags, MOVE_RESULT_NO_EFFECT, \jumpptr
	.endm

	.macro jumpifbattletype flags:req, jumpptr:req
	jumpifword CMP_COMMON_BITS, gBattleTypeFlags, \flags, \jumpptr
	.endm

	.macro jumpifnotbattletype flags:req, jumpptr:req
	jumpifword CMP_NO_COMMON_BITS, gBattleTypeFlags, \flags, \jumpptr
	.endm
