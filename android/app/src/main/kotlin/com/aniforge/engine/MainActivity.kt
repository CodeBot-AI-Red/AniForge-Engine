package com.aniforge.engine

import android.app.Activity
import android.os.Bundle
import android.widget.ImageView
import android.widget.TextView
import android.graphics.Color
import android.widget.LinearLayout
import android.view.Gravity

class MainActivity : Activity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        val layout = LinearLayout(this).apply {
            orientation = LinearLayout.VERTICAL
            setBackgroundColor(Color.BLACK)
            gravity = Gravity.CENTER
        }

        val logo = ImageView(this).apply {
            setImageResource(R.drawable.logo)
            layoutParams = LinearLayout.LayoutParams(500, 500).apply {
                gravity = Gravity.CENTER
            }
            scaleType = ImageView.ScaleType.FIT_CENTER
        }

        val subtitle = TextView(this).apply {
            text = "v1.0.0 — Inicializando..."
            textSize = 16f
            setTextColor(Color.WHITE)
            gravity = Gravity.CENTER
            setPadding(0, 20, 0, 0)
        }

        val status = TextView(this).apply {
            text = "✅ Engine carregada com sucesso"
            textSize = 14f
            setTextColor(Color.parseColor("#00ff88"))
            gravity = Gravity.CENTER
            setPadding(0, 10, 0, 0)
        }

        layout.addView(logo)
        layout.addView(subtitle)
        layout.addView(status)
        setContentView(layout)
    }
}
