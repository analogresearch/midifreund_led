# midifreund_led

DC IN: 9..28 V 

Ansteuerung durch MIDI note 36 (C2) und eine Oktave dur hoch bis C3.
also:
36 38 40 41 43 45 47 48

MIDI channel und Programm werden binär über DIP Schalter gewählt.

MIDI: Ausnahme DIP Schalter 0000 = MIDI channel 16!

programme:  
0 triggert durch note on einen kurzen 100% Blitz der auf 0 ausfaded.  
1 triggert durch note on einen kurzen Blitz mit Starthelligkeit velocity der dann auf 0 ausfaded.  
2 note on schaltet Led mit Helligkeit velocity ein. Helligkeit kann dann mit aftertouch poly moduliert werden. note off schaltet Led aus.  

![ein Bild](midifreund_led_foto.jpg?raw=true "ein Foto")