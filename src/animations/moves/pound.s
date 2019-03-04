.text
.thumb
.align 2
.include "src/animation_cmds.s"

.equ impact1Particle, 0x900B

.global PoundAnimation
PoundAnimation:
	startscript FireworkAnimation false
	fastsetbattlers
	loadspritefull impact1Sprite impact1Palette impact1Oam
	copyvar impact1Particle LASTRESULT
	sideof attacker
	if1 0x1 goto PoundAnimationOpponentsSide
	rendersprite impact1Particle targetx targety nullrsf
	movebg 1 5 3 2 false
	movesprite impact1Particle 1 3 3 true
	wait
	deletesprite impact1Particle
	movebg 1 0xFFFB 0xFFFD 2 false
	wait
	waittask TaskCreateSmallFireworkImpact
	end
	
PoundAnimationOpponentsSide:
	rendersprite impact1Particle targetx targety nullrsf
	movebg 1 0xFFFB 0xFFFD 2 false
	movesprite impact1Particle 1 3 3 true
	wait
	deletesprite impact1Particle
	movebg 1 5 3 2 false
	wait
	waittask TaskCreateSmallFireworkImpact
	end

.pool
