# Manual test plan

1. PIE starts and the player character spawns.
2. WASD movement responds through Enhanced Input.
3. Space attacks the nearest enemy within the configured radius.
4. Enemies navigate toward the player around collision obstacles.
5. Enemy damage reduces health and destruction increments score.
6. Clearing a wave starts the next wave after the configured delay.
7. HUD updates health, wave, enemy count and score.
8. Assign a Behavior Tree containing BTTask_ChasePlayer and verify AI movement.
