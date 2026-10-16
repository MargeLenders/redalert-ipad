/*
 * Copyright 2025 Electronic Arts Inc.
 *
 * Derived from Electronic Arts Inc.'s public source release for
 * Command & Conquer: Red Alert.
 * Licensed under GPLv3-or-later with additional Electronic Arts terms.
 * Modified for the macOS port, 2026.
 * See LICENSE.md.
 */

#ifdef WIN32

#include <windows.h>

class DDEServerClass {

	public:

		DDEServerClass (void);
		~DDEServerClass (void);


		char 	*Get_MPlayer_Game_Info (void);					//Returns pointer to game info
		int    Get_MPlayer_Game_Info_Length(){return(MPlayerGameInfoLength);};	//Len of game info
		BOOL	 Callback(unsigned char *data, long length);	//DDE callback function
		void	 Delete_MPlayer_Game_Info(void);					//release the game info memory
		void	 Enable(void);											//Enable the DDE callback
		void	 Disable(void);										//Disable the DDE callback
		int	 Time_Since_Heartbeat(void);						//Returns the time since the last hearbeat from WChat

		/*
		** Enumeration for DDE packet types from WChat
		*/
		enum {
			DDE_PACKET_START_MPLAYER_GAME,		//Start game packet. This includes game options
			DDE_PACKET_GAME_RESULTS,				//Game results packet. The game statistics.
			DDE_PACKET_HEART_BEAT,					//Heart beat packet so we know WChat is still there.
			DDE_TICKLE,									//Message to prompt other app to take focus.
			DDE_CONNECTION_FAILED
		};


	private:

		char 				*MPlayerGameInfo;			//Pointer to game start packet
		int				MPlayerGameInfoLength;	//Length of game start packet.
		BOOL				IsEnabled;					//Flag for DDE callback enable
		int				LastHeartbeat;		// Time since last heartbeat packet was received from WChat

};


extern DDEServerClass DDEServer;
extern BOOL Send_Data_To_DDE_Server (char *data, int length, int packet_type);


#endif	//WIN32
