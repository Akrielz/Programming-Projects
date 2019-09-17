///scr_change_bck(bck1, bck2)
bck1 = argument0;
bck2 = argument1;
if global.Special_Trigger == 0
{
    Delta = 0;
    global.Special_Trigger = 1
}

draw_background_ext(bck1, view_xview[0], view_yview[0], background_xscale[0], background_yscale[0], 0, c_white, 1-Delta);
draw_background_ext(bck2, view_xview[0], view_yview[0], background_xscale[0], background_yscale[0], 0, c_white, Delta);

if global.Trigger[global.Index] == 1
{
    if Delta < 1
        Delta += 0.016; 
} 
