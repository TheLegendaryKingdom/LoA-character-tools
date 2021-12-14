#include "Define.h"
#include "GossipDef.h"
#include "Item.h"
#include "Player.h"
#include "ScriptedGossip.h"
#include "ScriptMgr.h"
#include "Spell.h"
#include "Configuration/Config.h"
#include "Chat.h"

class character_tools : public ItemScript
{
public:
    character_tools() : ItemScript("character_tools") {}

    bool OnUse(Player* player, Item* item, SpellCastTargets const& /*targets*/) override
    {
        player->PlayerTalkClass->ClearMenus();

        if (player->IsInCombat())
            return false;

        if (!sConfigMgr->GetBoolDefault("CharacterTools", true))
            return false;

        AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Changer de |cff1EFF0CNOM|r", GOSSIP_SENDER_MAIN, 1, "Voulez-vous vraiment changer de |cff1EFF0CNOM|r ?\n\nCe service est irrévocable !\n", 0, false);
        AddGossipItemFor(player, GOSSIP_ICON_TABARD, "Changer d'|cffA335EEAPPARENCE|r", GOSSIP_SENDER_MAIN, 2, "Voulez-vous vraiment changer d'|cffA335EEAPPARENCE|r ?\n\nVous pourrez annuler ce service si vous changez d'avis.\n", 0, false);
        AddGossipItemFor(player, GOSSIP_ICON_TAXI, "Changer de |cffFFFC01RACE|r", GOSSIP_SENDER_MAIN, 3, "Voulez-vous vraiment changer de |cffFFFC01RACE|r ?\n\nVous pourrez annuler ce service si vous changez d'avis.\n", 0, false);
        AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Changer de |cffFF8000FACTION|r", GOSSIP_SENDER_MAIN, 4, "Voulez-vous vraiment changer de |cffFF8000FACTION|r ?\n\nVous pourrez annuler ce service si vous changez d'avis.\n", 0, false);
        SendGossipMenuFor(player, 60006, item->GetGUID());

        return false; // If item has spell cast it normal.
    }

    void OnGossipSelect(Player* player, Item* /*item*/, uint32 /*sender*/, uint32 action) override
    {
        player->PlayerTalkClass->ClearMenus();
        switch (action)
        {
            case 1:
                player->SetAtLoginFlag(AT_LOGIN_RENAME);
                ChatHandler(player->GetSession()).PSendSysMessage("CHAT OUTPUT: Please log out for name change.");
                break;
            case 2:
                player->SetAtLoginFlag(AT_LOGIN_CUSTOMIZE);
                ChatHandler(player->GetSession()).PSendSysMessage("CHAT OUTPUT: Please log out for Character Customize.");
                break;
            case 3:
                player->SetAtLoginFlag(AT_LOGIN_CHANGE_RACE);
                ChatHandler(player->GetSession()).PSendSysMessage("CHAT OUTPUT: Please log out for race change.");
                break;
            case 4:
                player->SetAtLoginFlag(AT_LOGIN_CHANGE_FACTION);
                ChatHandler(player->GetSession()).PSendSysMessage("CHAT OUTPUT: Please log out for faction change.");
                break;
        }
    }

};

void AddCharacterToolsScripts()
{
    new character_tools();
}
