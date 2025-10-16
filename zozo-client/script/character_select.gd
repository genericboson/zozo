extends Control

@onready var dropDown = $CharacterDropDown

func _physics_process(delta: float) -> void:
	dropDown.add_item()
