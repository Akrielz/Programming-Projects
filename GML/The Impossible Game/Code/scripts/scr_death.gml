
if ( global.checkpointR != 0 )
    room_goto(global.checkpointR);
else
    room_restart();
    
audio_stop_sound(snd_ChaosFantasy);


global.attempts ++;

/*

if ( obj_player.y > 900 )
    obj_player.y = 950;
