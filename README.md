# Attiny2313-IR-Receiver-nec

This is the code that runs in WinAVR and implements interrupt reception on the PD4 output of the microcontroller.

To summarize, the interrupt is triggered every time a wave falls. As a consequence, we record the time between dips, define it as 0 or 1 and write it to a variable in decimal form.

For the first 3 iterations we check that the incoming code is indeed NEC and is not just noise.

The remaining 4 iterations we sequentially write address, inverse address, command and inverse command, after writing it all we process the resulting decimal value.

The value 9 serves as an error signal and puts the interrupt in the initial state.
_________________________________________________________________________________

Это код, работающий в WinAVR и реализует прием сигнала по прерыванию на выходе PD4 микроконтроллера.

Говоря кратко, прерывание срабатывает каждый приход спада волны. В следствии чего, мы фиксируем время между спадами, определяем его как 0 или 1 и записываем в переменную в десятичном виде.

Первые 3 итерации мы проверяем, что пришедший код действительно NEC и не является просто помехами.

Остальные 4 итерации мы последовательно записываем адрес, инверсный адрес, команду и инверсную команду, после записи всего этого мы обрабатываем полученное десятичное значение.

Значение 9 служит сигналом об ошибке и ставит прерывание в исходное состояние.
