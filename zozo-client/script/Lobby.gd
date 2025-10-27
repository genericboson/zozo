extends Control

@onready var accountInput = $AccountInput
@onready var passwordInput = $PasswordInput

func _on_button_pressed() -> void:
	Global.socket_manager.SendLogin(accountInput.text,passwordInput.text)
	
	
func _on_setting_pressed() -> void:
	Global.message_box("개발 예정...")
	
func _add_password():
	print("signaled")
	#dropDown.add_item(password)

func _test(passwords: Array) -> void:
	get_tree().change_scene_to_file("res://scene/CharacterSelect.tscn")
	var dropDown = get_node("/root/CharacterSelect/CharacterDropDown")
	
	for password in passwords:
		dropDown.add_item(password)
	
