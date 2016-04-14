/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.h

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

#ifndef IR_SENSOR_H    /* Guard against multiple inclusion */
#define IR_SENSOR_H



/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif

    void forward(); // function to make car move forward
    void right_turn();// function to make car turn left
    void left_turn();//function to make car turn right
    
#endif /* _EXAMPLE_FILE_NAME_H */

/* *****************************************************************************
 End of File
 */
