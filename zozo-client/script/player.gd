extends CharacterBody2D

const speed = 400

@onready var stateAnim = $AnimatedSprite2D

func _physics_process(delta: float) -> void:
	if Input.is_action_pressed("left"):
		position.x -= speed * delta
		stateAnim.flip_h = true
		
		stateAnim.play("walk_side")
	elif Input.is_action_pressed("right"):
		position.x += speed * delta
		stateAnim.flip_h = false
		_AfterMove(position.x, position.y)
		stateAnim.play("walk_side")
	elif Input.is_action_just_released("left"):
		stateAnim.flip_h = true
		_AfterMove(position.x, position.y)
		stateAnim.play("idle_side")
	elif Input.is_action_just_released("right"):
		stateAnim.flip_h = false
		_AfterMove(position.x, position.y)
		stateAnim.play("idle_side")
		
	if Input.is_action_pressed("up"):
		position.y -= speed * delta
		_AfterMove(position.x, position.y)
		stateAnim.play("walk_back")
	elif Input.is_action_pressed("down"):
		position.y += speed * delta
		_AfterMove(position.x, position.y)
		stateAnim.play("walk_front")
	elif Input.is_action_just_released("up"):
		_AfterMove(position.x, position.y)
		stateAnim.play("idle_back")
	elif Input.is_action_just_released("down"):
		_AfterMove(position.x, position.y)
		stateAnim.play("idle_front")
		
	move_and_slide()

func _AfterMove(x:float, y:float) ->void:
	GDGlobal.socket_manager.SendCharacterMove(position.x, position.y)
	
	#region for debug position
	#var formatStr = "pos:[%f,%f]"
	#var actualStr = formatStr % [position.x,position.y]
	#print(actualStr)
	#endregion
