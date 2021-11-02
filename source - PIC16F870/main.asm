
_main:

;main.c,26 :: 		void main() {
;main.c,28 :: 		GIE_bit = 0x01;
	BSF        GIE_bit+0, BitPos(GIE_bit+0)
;main.c,29 :: 		PEIE_bit = 0x00;
	BCF        PEIE_bit+0, BitPos(PEIE_bit+0)
;main.c,30 :: 		INTE_bit = 0x01;
	BSF        INTE_bit+0, BitPos(INTE_bit+0)
;main.c,31 :: 		INTEDG_bit = 0x01;
	BSF        INTEDG_bit+0, BitPos(INTEDG_bit+0)
;main.c,33 :: 		TRISB = 0xFF;                                      // Set port B as input
	MOVLW      255
	MOVWF      TRISB+0
;main.c,34 :: 		TRISC = 0x81;
	MOVLW      129
	MOVWF      TRISC+0
;main.c,36 :: 		PORTA = 0x00;
	CLRF       PORTA+0
;main.c,37 :: 		PORTC = 0x00;
	CLRF       PORTC+0
;main.c,39 :: 		ADCON1 = 0x06;                                     // Set the analog pins as digital
	MOVLW      6
	MOVWF      ADCON1+0
;main.c,41 :: 		Lcd_Init();                                        // Initialize LCD
	CALL       _Lcd_Init+0
;main.c,42 :: 		Lcd_Cmd(_LCD_CURSOR_OFF);                          // Turn cursor off
	MOVLW      12
	MOVWF      FARG_Lcd_Cmd_out_char+0
	CALL       _Lcd_Cmd+0
;main.c,43 :: 		UART1_Init(9600);                                  // Initialize Uart module
	MOVLW      129
	MOVWF      SPBRG+0
	BSF        TXSTA+0, 2
	CALL       _UART1_Init+0
;main.c,44 :: 		Delay_ms(100);                                     // Await Uart to stabilize
	MOVLW      3
	MOVWF      R11+0
	MOVLW      138
	MOVWF      R12+0
	MOVLW      85
	MOVWF      R13+0
L_main0:
	DECFSZ     R13+0, 1
	GOTO       L_main0
	DECFSZ     R12+0, 1
	GOTO       L_main0
	DECFSZ     R11+0, 1
	GOTO       L_main0
	NOP
	NOP
;main.c,46 :: 		Lcd_Cmd(_LCD_CLEAR);
	MOVLW      1
	MOVWF      FARG_Lcd_Cmd_out_char+0
	CALL       _Lcd_Cmd+0
;main.c,47 :: 		Lcd_Out(1, (16-strlen("Powering up..."))/2, "Powering up...");
	MOVLW      ?lstr1_main+0
	MOVWF      FARG_strlen_s+0
	CALL       _strlen+0
	MOVF       R0+0, 0
	SUBLW      16
	MOVWF      R3+0
	MOVF       R0+1, 0
	BTFSS      STATUS+0, 0
	ADDLW      1
	CLRF       R3+1
	SUBWF      R3+1, 1
	MOVF       R3+0, 0
	MOVWF      R0+0
	MOVF       R3+1, 0
	MOVWF      R0+1
	RRF        R0+1, 1
	RRF        R0+0, 1
	BCF        R0+1, 7
	BTFSC      R0+1, 6
	BSF        R0+1, 7
	BTFSS      R0+1, 7
	GOTO       L__main11
	BTFSS      STATUS+0, 0
	GOTO       L__main11
	INCF       R0+0, 1
	BTFSC      STATUS+0, 2
	INCF       R0+1, 1
L__main11:
	MOVF       R0+0, 0
	MOVWF      FARG_Lcd_Out_column+0
	MOVLW      1
	MOVWF      FARG_Lcd_Out_row+0
	MOVLW      ?lstr2_main+0
	MOVWF      FARG_Lcd_Out_text+0
	CALL       _Lcd_Out+0
;main.c,48 :: 		do{
L_main1:
;main.c,49 :: 		if(UART1_Data_Ready()) incoming_data = UART1_Read(); // Read the incoming data
	CALL       _UART1_Data_Ready+0
	MOVF       R0+0, 0
	BTFSC      STATUS+0, 2
	GOTO       L_main4
	CALL       _UART1_Read+0
	MOVF       R0+0, 0
	MOVWF      _incoming_data+0
L_main4:
;main.c,50 :: 		if(incoming_data == 0x07){
	MOVF       _incoming_data+0, 0
	XORLW      7
	BTFSS      STATUS+0, 2
	GOTO       L_main5
;main.c,51 :: 		GetIncomingText();
	CALL       _GetIncomingText+0
;main.c,52 :: 		while(1){}
L_main6:
	GOTO       L_main6
;main.c,53 :: 		}
L_main5:
;main.c,54 :: 		else if(incoming_data == 0x1A){
	MOVF       _incoming_data+0, 0
	XORLW      26
	BTFSS      STATUS+0, 2
	GOTO       L_main9
;main.c,55 :: 		AddFeedInfo();
	CALL       _AddFeedInfo+0
;main.c,56 :: 		}
L_main9:
;main.c,57 :: 		} while(incoming_data != 0x17);
	MOVF       _incoming_data+0, 0
	XORLW      23
	BTFSS      STATUS+0, 2
	GOTO       L_main1
;main.c,59 :: 		Lcd_Cmd(_LCD_CLEAR);
	MOVLW      1
	MOVWF      FARG_Lcd_Cmd_out_char+0
	CALL       _Lcd_Cmd+0
;main.c,60 :: 		Lcd_Out(1, (16-strlen("Auto Pet Feeder"))/2, "Auto PetFeeder"); // Write centralized message
	MOVLW      ?lstr3_main+0
	MOVWF      FARG_strlen_s+0
	CALL       _strlen+0
	MOVF       R0+0, 0
	SUBLW      16
	MOVWF      R3+0
	MOVF       R0+1, 0
	BTFSS      STATUS+0, 0
	ADDLW      1
	CLRF       R3+1
	SUBWF      R3+1, 1
	MOVF       R3+0, 0
	MOVWF      R0+0
	MOVF       R3+1, 0
	MOVWF      R0+1
	RRF        R0+1, 1
	RRF        R0+0, 1
	BCF        R0+1, 7
	BTFSC      R0+1, 6
	BSF        R0+1, 7
	BTFSS      R0+1, 7
	GOTO       L__main12
	BTFSS      STATUS+0, 0
	GOTO       L__main12
	INCF       R0+0, 1
	BTFSC      STATUS+0, 2
	INCF       R0+1, 1
L__main12:
	MOVF       R0+0, 0
	MOVWF      FARG_Lcd_Out_column+0
	MOVLW      1
	MOVWF      FARG_Lcd_Out_row+0
	MOVLW      ?lstr4_main+0
	MOVWF      FARG_Lcd_Out_text+0
	CALL       _Lcd_Out+0
;main.c,61 :: 		}
L_end_main:
	GOTO       $+0
; end of _main
