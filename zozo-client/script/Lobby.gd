extends Control

@onready var accountInput = $AccountInput
@onready var passwordInput = $PasswordInput
@onready var serverSelect = $ServerSelect

func _on_ready() -> void:
	serverSelect.add_item("Choose server")
	Global.socket_manager.SendServerListReq()

func _on_button_pressed() -> void:
	Global.account = accountInput.text
	Global.socket_manager.SendAuthReq(accountInput.text,passwordInput.text)
	
func _on_setting_pressed() -> void:
	Global.message_box("개발 예정...")
	
func _add_password():
	print("signaled")
	#dropDown.add_item(password)
