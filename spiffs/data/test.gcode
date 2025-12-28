; ==========================================
; Ukazkovy G-CODE pro roboticke rameno
; ==========================================
; Popis: Testovaci sekvence pohybu
; Jednotky: mm (G21)
; Souradnice: Absolutni (G90)
; ==========================================

; 1. Nastaveni rezimu
G21             ; Nastavit jednotky na milimetry
G90             ; Nastavit absolutni pozicovani

; 2. Vychozi pozice (HOME) - bezpecna vyska
; Predpoklad: X0 Y150 je stred pred robotem
G1 X0 Y150 Z150 F1000  ; F = rychlost posuvu

; 3. Presun nad bod A (Odber)
G1 X100 Y100 Z100
G4 P500         ; Pauza 500ms (cekani na ustaleni)

; 4. Klesnuti dolu k bodu A
G1 X100 Y100 Z20
G4 P1000        ; Pauza 1 sekunda (simulace uchopu)

; 5. Zvednuti zpet nahoru
G1 X100 Y100 Z100

; 6. Presun nad bod B (Odlozeni - na opacne strane)
G1 X-100 Y100 Z100

; 7. Klesnuti k bodu B
G1 X-100 Y100 Z20
G4 P1000        ; Pauza 1 sekunda (simulace polozeni)

; 8. Zvednuti a navrat domu
G1 X-100 Y100 Z150
G1 X0 Y150 Z150

; Konec programu
M30