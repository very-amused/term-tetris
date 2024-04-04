.section rodata

DB_schema_start:
	.incbin "sql/schema.sql"

DB_schema_end:
	.byte 0 # Null terminate

.global DB_schema
.type DB_schema, @object
.balign 8
DB_schema:
	.quad DB_schema_start

.global DB_schema_len
.type DB_schema_len, @object
.balign 8
DB_schema_len:
	.quad DB_schema_end - DB_schema_start
