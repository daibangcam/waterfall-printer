Note:
- Configure Tab size in KeilC & Notepad++ to 4 blanks

Create new project in workspace
- copy the old folder of the old project
- change the name of folder to the name of the new project
- delete all files except .uvproj, change the name of this file to name of new project
- delete all files in folder \Obj, go to tab Output of KeilC's option and change the name of output file
- rebuild and reopen the workspace, then add this new project to workspace

Template for function description
/*******************************************************************************
 * @fn     BUT_SEL_IsPress     
 * @brief  Return the pin's state: value 1 means that button is pressed
 * @param  a: xxx
 * @retval Button is pressed or not
 *      This return value can be one of the following values:
 *          @arg TRUE
 *          @arg FALSE
 * @note
*******************************************************************************/
