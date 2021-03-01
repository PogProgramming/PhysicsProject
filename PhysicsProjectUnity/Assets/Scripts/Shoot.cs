using System.Collections;
using System.Collections.Generic;
using UnityEditor;
using UnityEngine;

public class Shoot : MonoBehaviour
{
    public GameObject bullet = null;
    public GameObject orientation = null;
    public GameObject gunEndPoint = null; // To help with rotation of bullet

    public float cooldown = 0.2f;
    bool canShoot = true;

    public float gunDamage = 0;
    public float gunBulletSpeed = 0;

    public LayerMask enemyLayer;


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
        Camera cam = Camera.main;
        GameObject bulletObj = GameObject.Instantiate(bullet, gunEndPoint.transform.position, gunEndPoint.transform.rotation);
        BulletAttack ba = bulletObj.GetComponent<BulletAttack>();

        ba.SetBullet(gunDamage, gunBulletSpeed, cam.transform.forward);

        RaycastHit hit;
        if (Physics.Raycast(gunEndPoint.transform.position, cam.transform.forward, out hit, enemyLayer))
        {
            GameObject mainEnemyBody = hit.transform.gameObject;
            bool checkGood = false;
            while (mainEnemyBody.transform.name != "EnemyPlayer" || mainEnemyBody.transform.name != "EnemyPlayer(Clone)")
            {
                if (mainEnemyBody.transform.parent == null)
                    break;
                mainEnemyBody = mainEnemyBody.transform.parent.gameObject;

                if (mainEnemyBody.transform.name == "EnemyPlayer" || mainEnemyBody.transform.name == "EnemyPlayer(Clone)")
                    checkGood = true;
            }
            if (checkGood)
            {
                Debug.Log("HELP HELP IM DYING");
                mainEnemyBody.transform.GetComponent<EnemyHealth>().TakeDamage(gunDamage, hit.normal, gunBulletSpeed, hit.transform.GetComponent<Rigidbody>());
            }
        }

    }
}
