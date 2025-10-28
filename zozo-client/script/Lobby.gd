extends Control

@onready var accountInput = $AccountInput
@onready var passwordInput = $PasswordInput

func _on_button_pressed() -> void:
	Global.socket_manager.SendAuthReq(accountInput.text,passwordInput.text)
	
func _on_setting_pressed() -> void:
	Global.message_box("개발 예정...")
	
func _add_password():
	print("signaled")
	#dropDown.add_item(password)
	
func consumeAuthAck(authResult: int) -> void:
	match authResult:
		0:
			get_tree().change_scene_to_file("res://scene/CharacterSelect.tscn")
		2:
			Global.message_box("Wrong password")
		_:
			Global.message_box("Logic error")
