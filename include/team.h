#pragma once

#include <trainer.h>

/* TEAM */
typedef struct 
{
    
    /* About Team*/
    Objective global;
    int team_size;
    Trainer* team[];

} Team;
