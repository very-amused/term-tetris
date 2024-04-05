.section .rodata

.global DB_schema
.type DB_schema, @object
DB_schema:
	.incbin "sql/schema.sql"
DB_schema_end:
	.byte 0 # Null terminate

.global DB_schema_len
.type DB_schema_len, @object
.balign 8
DB_schema_len:
	.quad DB_schema_end - DB_schema
