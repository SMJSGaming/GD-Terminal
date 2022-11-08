#pragma once

#include "../includes.hpp"

namespace gd {
    struct GameLevelManagerExt : public CCNode {
        static GameLevelManagerExt* sharedState() {
            return reinterpret_cast<GameLevelManagerExt*(__stdcall*)()>(gd::base + 0x9f860)();
        }

        cocos2d::CCDictionary* m_mainLevels;
        cocos2d::CCDictionary* m_searchFilters;
        cocos2d::CCDictionary* m_onlineLevels;
        PAD(0x4)
        cocos2d::CCDictionary* m_followedCreators;
        cocos2d::CCDictionary* m_downloadedLevels;
        cocos2d::CCDictionary* m_likedLevels;
        cocos2d::CCDictionary* m_ratedLevels;
        cocos2d::CCDictionary* m_ratedDemons;
        cocos2d::CCDictionary* m_reportedLevels;
        cocos2d::CCDictionary* m_onlineFolders;
        cocos2d::CCDictionary* m_localLevelsFolders;
        cocos2d::CCDictionary* m_dailyLevels;
        int m_dailyTimeLeft;
        int m_dailyID;
        int m_dailyIDUnk;
        PAD(0x4)
        int m_weeklyTimeLeft;
        int m_weeklyID;
        int m_weeklyIDUnk;
        cocos2d::CCDictionary* m_gauntletLevels;
        cocos2d::CCDictionary* m_unkDict13;
        PAD(0x4)
        cocos2d::CCDictionary* m_timerDict;
        cocos2d::CCDictionary* m_knownUsers;
        cocos2d::CCDictionary* m_accountIDtoUserIDDict;
        cocos2d::CCDictionary* m_userIDtoAccountIDDict;
        cocos2d::CCDictionary* m_storedLevels;
        cocos2d::CCDictionary* m_pageInfo;
        cocos2d::CCDictionary* m_unkDict20;
        cocos2d::CCDictionary* m_savedPacks;
        cocos2d::CCDictionary* m_savedGauntlets;
        cocos2d::CCDictionary* m_downloadObjects;
        cocos2d::CCDictionary* m_unkDict24;
        cocos2d::CCDictionary* m_storedUserInfo;
        cocos2d::CCDictionary* m_friendRequests;
        cocos2d::CCDictionary* m_userMessages;
        cocos2d::CCDictionary* m_userReplies;
        std::string m_unkStr1;
        std::string m_unkStr2;
        LeaderboardState m_leaderboardState;
        bool m_unkEditLevelLayerOnBack;
        PAD(0x4)
        LevelDownloadDelegate* m_levelDownloadDelegate;
        LevelCommentDelegate* m_levelCommentDelegate;
        CommentUploadDelegate* m_commentUploadDelegate;
        PAD(0x4)
        LevelUpdateDelegate* m_levelUpdateDelegate;
        LeaderboardManagerDelegate* m_leaderboardManagerDelegate;
        LevelDeleteDelegate* m_levelDeleteDelegate;
        UserInfoDelegate* m_userInfoDelegate;
        PAD(0x4)
        void* m_unkDelegate;
        PAD(0x1C)
        MusicDownloadDelegate* m_musicDownloadDelegate;
        int m_unkDownload;
        PAD(0x4)
        std::string m_unkStr3;
        cocos2d::CCString* m_unkStr4;

        bool downloadLevel(int id, bool unk) {
            return reinterpret_cast<bool(__thiscall*)(GameLevelManagerExt*, int, bool)>(gd::base + 0xAA730)(this, id, unk);
        }
    };
}