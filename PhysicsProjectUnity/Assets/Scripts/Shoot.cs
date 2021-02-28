using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Shoot : MonoBehaviour
{
    public GameObject bullet = null;
    public GameObject orientation = null;

    public float cooldown = 0.2f;
    bool canShoot = true;

    public float gunDamage = 0;
    public float gunBulletSpeed = 20;


    void Start()
    {

    }

    // Update is called once per frame
    float timer = 0;
    void Update()
    {
        if (Input.GetMouseButton(0))
            InputShoot();

        if (timer < cooldown)
            timer += Time.deltaTime;
        else
        {
            if (!canShoot) canShoot = true;
        }
    }

    void InputShoot()
    {
        if (canShoot)
        {
            canShoot = false;
            timer = 0;
            ShootBullet();
        }
    }

    void ShootBullet()
    {
        GameObject bulletObj = GameObject.Instantiate(bullet, Camera.main.transform.position, Camera.main.transform.rotation);
        BulletAttack ba = bulletObj.GetComponent<BulletAttack>();

        ba.SetBullet(gunDamage, gunBulletSpeed, Camera.main.transform.forward);
    }
}
