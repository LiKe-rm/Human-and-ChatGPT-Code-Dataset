#include <iostream>
#include <string>
#include <vector>

namespace RakMagic
{
    namespace AI
    {
        enum RSTATE
        {
            RSTATE_ONFOOT,
            RSTATE_DRIVER,
            RSTATE_PASSENGER,
            RSTATE_SPECTATING,
            RSTATE_NONE
        };

        struct Vector3
        {
            float x;
            float y;
            float z;
        };

        struct INCAR_SYNC_DATA
        {
            unsigned short vehicleID;
            unsigned char passengerSlot;
            Vector3 position;
            Vector3 speed;
            float quaternion[4];
            unsigned char health;
            unsigned char armor;
            unsigned char currentWeapon;
            unsigned char sirenState;
            unsigned char landingGearState;
            unsigned char trailerID;
        };

        struct ONFOOT_SYNC_DATA
        {
            unsigned char lrAnalog;
            unsigned char udAnalog;
            unsigned char wKeys;
            Vector3 position;
            Vector3 aimf;
            float health;
            unsigned char currentWeapon;
            unsigned char specialAction;
            Vector3 velocity;
            float quaternion[4];
            unsigned char animation;
        };

        struct AIM_SYNC_DATA
        {
            unsigned char camMode;
            Vector3 camPos;
            Vector3 aimf;
            unsigned char aimState;
            Vector3 camFov;
        };

        struct SPECTATOR_SYNC_DATA
        {
            Vector3 position;
            float rotation;
            unsigned char mode;
            unsigned short vehicleID;
        };

        struct BULLET_SYNC_DATA
        {
            unsigned short targetID;
            Vector3 position;
            Vector3 velocity;
            unsigned char hitType;
        };

        class Player
        {
            public:
            Player(int id, bool invisible = false)
                : m_id(id), m_bInvisible(invisible), m_iState(RSTATE_ONFOOT)
            {
            }

            int GetID() const { return m_id; }
            bool IsInvisible() const { return m_bInvisible; }
            RSTATE GetState() const { return m_iState; }
            void SetState(RSTATE state) { m_iState = state; }

            void UpdateOnfoot()
            {
                if (m_bInvisible)
                {
                    SPECTATOR_SYNC_DATA data;
                    // fill data with spectator sync data
                    // ...

                    // send data
                    // ...
                } else
                {
                    ONFOOT_SYNC_DATA data;
                    // fill data with onfoot sync data
                    // ...

                    // send data
                    // ...
                }
            }

            void UpdateVehicle(unsigned short vehicleID)
            {
                if (vehicleID == 0)
                {
                    return;
                }

                INCAR_SYNC_DATA data;
                // fill data with vehicle sync data
                // ...

                // send data
                // ...

                m_iState = RSTATE_DRIVER;
            }

            void UpdateFollow(Player* pTarget, float fDistance)
            {
                if (pTarget == nullptr)
                {
                    return;
                }

                if (pTarget->GetState() == RSTATE_DRIVER)
                {
                    // check if vehicle exists
                    // ...

                    if (/* vehicle exists */)
                    {
                        INCAR_SYNC_DATA data;
                        // fill data with vehicle sync data
                        // ...

                        // send data
                        // ...
                    } else
                    {
                        // player is passenger
                        // send vehicle data directly
                        // ...
                    }
                } else
                {
                    ONFOOT_SYNC_DATA onfootData;
                    AIM_SYNC_DATA aimData;
                    // fill onfootData and aimData with sync data
                    // ...

                    // modify data based on configuration
                    // ...

                    // send data
                    // ...
                }

                // teleport to target if too far away
                if (fDistance > /* max distance */)
                {
                    // teleport to target
                    // ...
                }
            }

            void UpdateFollowBullet(const BULLET_SYNC_DATA& data)
            {
                if (/* filter data */)
                {
                    return;
                }

                // send data
                // ...
            }

            private:
            int m_id;
            bool m_bInvisible;
            RSTATE m_iState;
        };

        std::vector<Player*> g_players;

        void UpdatePlayers()
        {
            for (auto pPlayer : g_players)
            {
                switch (pPlayer->GetState())
                {
                    case RSTATE_ONFOOT:
                        pPlayer->UpdateOnfoot();
                        break;
                    case RSTATE_DRIVER:
                    case RSTATE_PASSENGER:
                        pPlayer->UpdateVehicle(/* vehicle ID */);
                        break;
                    case RSTATE_SPECTATING:
                        // not implemented
                        break;
                    default:
                        break;
                }
            }
        }
    }
}

int main()
{
// initialize players
// ...
    RakMagic::AI::UpdatePlayers();

    return 0;
}