package com.aniforge.engine

import android.os.Bundle
import androidx.appcompat.app.AppCompatActivity
import androidx.fragment.app.FragmentManager
import com.aniforge.engine.fragments.SplashFragment
import com.aniforge.engine.fragments.HomeFragment

class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        if (savedInstanceState == null) {
            // Mostra splash primeiro
            showSplashScreen()
        }
    }

    private fun showSplashScreen() {
        supportFragmentManager.beginTransaction()
            .replace(R.id.fragment_container, SplashFragment())
            .addToBackStack(null)
            .commit()
    }

    fun showHomeScreen() {
        supportFragmentManager.beginTransaction()
            .replace(R.id.fragment_container, HomeFragment())
            .setReorderingAllowed(true)
            .commit()
    }
}
