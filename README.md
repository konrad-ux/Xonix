# Xonix Game
autorzy Konrad Zawiślak, Filip Zaleski

Aby uruchomić program postępuj zgodnie z instrukcjami

## Konfiguracja SFML w Visual Studio

1. Pobierz SFML ze strony: https://www.sfml-dev.org/download.php
2. Wypakuj do katalogu np. `C:\Libraries\SFML-2.6.1`
3. W Visual Studio:
   - Otwórz **Property Manager** (View → Other Windows → Property Manager)
   - Dla każdej konfiguracji (Debug | x64 i Release | x64):
     - Kliknij prawym przyciskiem myszy i wybierz **Add Existing Property Sheet...**
     - Wybierz `dependencies/SFML.props`
4. Upewnij się, że w katalogu z `.exe` znajdują się pliki `.dll` z katalogu `SFML-2.6.1\bin`

Program jest gotowy do uruchomienia.

