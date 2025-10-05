extends CharacterBody2D

const speed = 9600

@onready var stateAnim = $AnimatedSprite2D

func _physics_process(delta: float) -> void:
	if Input.is_action_pressed("left"):
		velocity.x = -speed * delta
		stateAnim.flip_h = true
		stateAnim.play("walk_side")
	elif Input.is_action_pressed("right"):
		velocity.x = speed * delta
		stateAnim.flip_h = false
		stateAnim.play("walk_side")
	elif Input.is_action_just_released("left"):
		velocity.x = 0
		stateAnim.flip_h = true
		stateAnim.play("idle_side")
	elif Input.is_action_just_released("right"):
		velocity.x = 0
		stateAnim.flip_h = false
		stateAnim.play("idle_side")
		
	if Input.is_action_pressed("up"):
		velocity.y = -speed * delta
		stateAnim.play("walk_back")
	elif Input.is_action_pressed("down"):
		velocity.y = speed * delta
		stateAnim.play("walk_front")
		pass
	elif Input.is_action_just_released("up"):
		velocity.y = 0
		stateAnim.play("idle_back")
		pass
	elif Input.is_action_just_released("down"):
		velocity.y = 0
		stateAnim.play("idle_front")
		pass
		
	move_and_slide()
